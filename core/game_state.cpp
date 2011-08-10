#include <cstdlib>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <pthread.h>

#include "game_state.h"
#include "os_calls.h"

GameState::GameState() :
    level(1),
    sector(1),
    highestLevel(1),
    highestSector(1),
    levelsInSector(1),
    sectorsInGalaxy(1),
    activePlanetInUse(false),
    activePlanetPlaced(false),
    stopLooping(true),
    importer(*this),
    menuOn(false),
    musicMuted(false),
    efxMuted(false),
    engine(*this)
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

    // Set up menu buttons
    menuButton.x = (0*BUTTON_WIDTH)+WIDTH*2/BOTTOM_BUTTONS-WIDTH-BUTTON_WIDTH_HALF;
    menuButton.y = -WIDTH/aspectRatio+BUTTON_HEIGHT_HALF;
    menuButton.widthHalf = BUTTON_WIDTH_HALF;
    menuButton.heightHalf = BUTTON_HEIGHT_HALF;
    lightPlanetButton.x = (1*BUTTON_WIDTH)+WIDTH*2/BOTTOM_BUTTONS-WIDTH-BUTTON_WIDTH_HALF;
    lightPlanetButton.y = -WIDTH/aspectRatio+BUTTON_HEIGHT_HALF;
    lightPlanetButton.widthHalf = BUTTON_WIDTH_HALF;
    lightPlanetButton.heightHalf = BUTTON_HEIGHT_HALF;
    mediumPlanetButton.x = (2*BUTTON_WIDTH)+WIDTH*2/BOTTOM_BUTTONS-WIDTH-BUTTON_WIDTH_HALF;
    mediumPlanetButton.y = -WIDTH/aspectRatio+BUTTON_HEIGHT_HALF;
    mediumPlanetButton.widthHalf = BUTTON_WIDTH_HALF;
    mediumPlanetButton.heightHalf = BUTTON_HEIGHT_HALF;
    heavyPlanetButton.x = (3*BUTTON_WIDTH)+WIDTH*2/BOTTOM_BUTTONS-WIDTH-BUTTON_WIDTH_HALF;
    heavyPlanetButton.y = -WIDTH/aspectRatio+BUTTON_HEIGHT_HALF;
    heavyPlanetButton.widthHalf = BUTTON_WIDTH_HALF;
    heavyPlanetButton.heightHalf = BUTTON_HEIGHT_HALF;
    antiPlanetButton.x = (4*BUTTON_WIDTH)+WIDTH*2/BOTTOM_BUTTONS-WIDTH-BUTTON_WIDTH_HALF;
    antiPlanetButton.y = -WIDTH/aspectRatio+BUTTON_HEIGHT_HALF;
    antiPlanetButton.widthHalf = BUTTON_WIDTH_HALF;
    antiPlanetButton.heightHalf = BUTTON_HEIGHT_HALF;
}

void GameState::mainLoop()
{
    // Buff, for future use.
    //char buff[500];

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

            // Hide any unwanted buttons that may be showing
            menuButton.buttonOnScreen = true;
            lightPlanetButton.buttonOnScreen = false;
            mediumPlanetButton.buttonOnScreen = false;
            heavyPlanetButton.buttonOnScreen = false;
            antiPlanetButton.buttonOnScreen = false;

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

            // Import the sector
            importer.loadSector(sector);
            pthread_mutex_lock(&dataLoadingMutex);
            dataNeedsLoading = true;
            pthread_mutex_unlock(&dataLoadingMutex);
            pthread_mutex_lock(&miscMutex);
            sectorName = "Really name this zone";
            pthread_mutex_unlock(&miscMutex);

            // Hide any unwanted buttons that may be showing
            menuButton.buttonOnScreen = true;
            lightPlanetButton.buttonOnScreen = false;
            mediumPlanetButton.buttonOnScreen = false;
            heavyPlanetButton.buttonOnScreen = false;
            antiPlanetButton.buttonOnScreen = false;

            // Start up the sector
            pthread_mutex_lock(&modeMutex);
            mode = MODE_GALACTIC_SECTOR_MENU;
            pthread_mutex_unlock(&modeMutex);

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

            // Show the buttons
            menuButton.buttonOnScreen = true;
            lightPlanetButton.buttonOnScreen = true;
            mediumPlanetButton.buttonOnScreen = true;
            heavyPlanetButton.buttonOnScreen = true;
            antiPlanetButton.buttonOnScreen = true;

            // Finay, start the level.
            getTime(timer);
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
            wonLevelButton.buttonOnScreen = true;
            wonLevelButton.x = 0;
            wonLevelButton.y = 0;
            wonLevelButton.widthHalf = 50;
            wonLevelButton.heightHalf = 50;
            break;
        case MODE_LEVEL_LOST:
            pthread_mutex_unlock(&modeMutex);
            lostLevelButton.buttonOnScreen = true;
            lostLevelButton.x = 0;
            lostLevelButton.y = 0;
            lostLevelButton.widthHalf = 50;
            lostLevelButton.heightHalf = 50;
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
