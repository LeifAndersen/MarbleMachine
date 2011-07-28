#include <cstdlib>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <pthread.h>

#include "game_state.h"
#include "os_calls.h"

GameState::GameState() : level(0), sector(0), highestLevel(0),
    highestSector(0), stopLooping(true), importer(*this),  engine(*this)
{    
    // Set up mutexs
   assert(!pthread_mutex_init(&modeMutex, NULL));
   assert(!pthread_mutex_init(&stopLoopingMutex, NULL));
   assert(!pthread_mutex_init(&planetsMutex, NULL));
   assert(!pthread_mutex_init(&soundMutex, NULL));
   assert(!pthread_mutex_init(&miscMutex, NULL));
   assert(!pthread_mutex_init(&dataLoadingMutex, NULL));

   // set up matrix:
   projectionMatrix.loadIdentity();
   projectionMatrix.ortho(-WIDTH, WIDTH, -WIDTH,
                          WIDTH, -WIDTH, WIDTH);

   // set up time
   timer = initTimer();

   // Seed the random number
   srand(MMtime());
}

GameState::~GameState()
{
    // Free mutexes
    assert(!pthread_mutex_destroy(&modeMutex));
    assert(!pthread_mutex_destroy(&stopLoopingMutex));
    assert(!pthread_mutex_destroy(&planetsMutex));
    assert(!pthread_mutex_destroy(&soundMutex));
    assert(!pthread_mutex_destroy(&miscMutex));
    assert(!pthread_mutex_destroy(&dataLoadingMutex));

    // Free timer
    deleteTimer(timer);
}

void GameState::setAspectRatio(float width, float height)
{
    aspectRatio = width/height;

    // set up matrix:
    projectionMatrix.loadIdentity();
    projectionMatrix.ortho(-WIDTH, WIDTH,
                           -WIDTH/aspectRatio, WIDTH/aspectRatio, -WIDTH, WIDTH);
}

void GameState::mainLoop()
{
    // Buff, for future use.
    char buff[500];

    // Set up an initial time2 for time delta
    getTime(timer);

    // main loop
    while(true) {

        // Other stuff to be done depending on mode
        pthread_mutex_lock(&modeMutex);
        switch(mode) {
        case MODE_GALACTIC_MENU_SETUP:
            pthread_mutex_unlock(&modeMutex);

            // Load the game
            importer.loadGalaxy();
            pthread_mutex_lock(&dataLoadingMutex);
            dataNeedsLoading = true;
            pthread_mutex_unlock(&dataLoadingMutex);

            // Start the music, load sounds

            // Start the game
            pthread_mutex_lock(&modeMutex);
            mode = MODE_GALACTIC_MENU;
            pthread_mutex_unlock(&modeMutex);
            break;
        case MODE_GALACTIC_MENU:
            pthread_mutex_unlock(&modeMutex);
            break;
        case MODE_GALACTIC_SECTOR_MENU_SETUP:
            pthread_mutex_unlock(&modeMutex);

            // Import the zone
            importer.loadSector(sector);
            pthread_mutex_lock(&miscMutex);
            sectorName = "Really name this zone";
            pthread_mutex_unlock(&miscMutex);

            // Start music and load sounds
            stopMusic();
            snprintf(buff, 500, "music_%u", sector);
            playMusic(buff);

            break;
        case MODE_GALACTIC_SECTOR_MENU:
            pthread_mutex_unlock(&modeMutex);
            break;
        case MODE_LEVEL_SETUP:
            pthread_mutex_unlock(&modeMutex);

            // Import the level
            importer.loadLevel(sector, level);
            pthread_mutex_lock(&miscMutex);
            levelName = "Set a real name";
            pthread_mutex_unlock(&miscMutex);

            // Start music and load sounds
            snprintf(buff, 500, "music_%u_%u", sector, level);
            stopMusic();
            playMusic(buff);

            // Finay, start the level.
            pthread_mutex_lock(&modeMutex);
            mode = MODE_LEVEL;
            pthread_mutex_unlock(&modeMutex);
            break;
        case MODE_LEVEL:
            pthread_mutex_unlock(&modeMutex);
            engine.update((float)((float)getTime(timer)*0.00000001f));
            break;
        case MODE_LEVEL_WON:
            pthread_mutex_unlock(&modeMutex);
            break;
        case MODE_LEVEL_MENU:
            pthread_mutex_unlock(&modeMutex);
            break;
        default:
            pthread_mutex_unlock(&modeMutex);
            break;
        }

        // Check to see if we need to stop looping
        pthread_mutex_lock(&stopLoopingMutex);
        if(stopLooping) {
            pthread_mutex_unlock(&stopLoopingMutex);
            return;
        }
        pthread_mutex_unlock(&stopLoopingMutex);
    }
}
