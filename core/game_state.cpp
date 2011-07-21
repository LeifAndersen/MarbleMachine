#include <cstdlib>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <pthread.h>

#include "game_state.h"
#include "os_calls.h"

GameState::GameState() : stopLooping(true),
    importer(*this),  engine(*this), menu(*this)
{    
    // Set up mutexs
   assert(!pthread_mutex_init(&modeMutex, NULL));
   assert(!pthread_mutex_init(&stopLoopingMutex, NULL));
   assert(!pthread_mutex_init(&planetsMutex, NULL));

   // set up matrix:
   projectionMatrix.loadIdentity();
   projectionMatrix.ortho(-10.0f*aspectRatio, 10.0f*aspectRatio, -10.0f, 10.0f, -10.0f, 10.0f);

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

    // Free timer
    deleteTimer(timer);
}

void GameState::setAspectRatio(float width, float height)
{
    aspectRatio = width/height;

    // set up matrix:
    projectionMatrix.loadIdentity();
    projectionMatrix.ortho(-10.0f, 10.0f,
                           -10.0f/aspectRatio, 10.0f/aspectRatio, -10.0f, 10.0f);
}

void GameState::mainLoop()
{
    // Set up an initial time2 for time delta
    getTime(timer);

    // main loop
    while(true) {

        // Other stuff to be done depending on mode
        pthread_mutex_lock(&modeMutex);
        switch(mode) {
        case MODE_GALACTIC_MENU:
            pthread_mutex_unlock(&modeMutex);
            break;
        case MODE_GALACTIC_ZONE_MENU:
            pthread_mutex_unlock(&modeMutex);
            break;
        case MODE_LEVEL_SETUP:
            pthread_mutex_unlock(&modeMutex);
            importer.loadLevel(1, level);
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
