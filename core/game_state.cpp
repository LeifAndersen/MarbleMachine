#include <cstdlib>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <pthread.h>
#include <ctime>

#include "game_state.h"
#include "os_calls.h"

GameState::GameState() : grid(FIELD_CHUNK_SIZE, FIELD_SIZE, FIELD_SIZE),
    stopLooping(true), engine(*this), menu(*this), importer(*this),
    time1older(true)
{
    // Set up mutexs
   assert(!pthread_mutex_init(&modeMutex, NULL));
   assert(!pthread_mutex_init(&stopLoopingMutex, NULL));

   // set up matrix:
   projectionMatrix.loadIdentity();
   projectionMatrix.ortho(-10.0f*aspectRatio, 10.0f*aspectRatio, -10.0f, 10.0f, -10.0f, 10.0f);

   // set up time
   clock_gettime(CLOCK_MONOTONIC, &time1);
   clock_gettime(CLOCK_MONOTONIC, &time2);
   time1long = (long)time1.tv_sec*1000000000LL + time1.tv_nsec;
   time2long = (long)time2.tv_sec*1000000000LL + time2.tv_nsec;
}

GameState::~GameState()
{
    // Free mutexes
    assert(!pthread_mutex_destroy(&modeMutex));
    assert(!pthread_mutex_destroy(&stopLoopingMutex));
}

void GameState::setAspectRatio(float width, float height)
{
    aspectRatio = width/height;

    // set up matrix:
    projectionMatrix.loadIdentity();
    projectionMatrix.ortho(-10.0f*aspectRatio, 10.0f*aspectRatio, -10.0f, 10.0f, -10.0f, 10.0f);
}

void GameState::mainLoop()
{
    bool time1older = true;
    clock_gettime(CLOCK_MONOTONIC, &time2);
    time2long = (long)time2.tv_sec*1000000000LL + time2.tv_nsec;
    while(true) {
        pthread_mutex_lock(&marble.mvMatrixMutex);
        marble.loadMVMatrix();
        marble.mvMatrix.matrix = (marble.mvMatrix*projectionMatrix).matrix;
        pthread_mutex_unlock(&marble.mvMatrixMutex);
        pthread_mutex_lock(&modeMutex);
        switch(mode) {
        case MENU_MODE:
            pthread_mutex_unlock(&modeMutex);
            break;
        case SET_UP_MODE:
            pthread_mutex_unlock(&modeMutex);
            break;
        case RUNNING_MODE:
            pthread_mutex_unlock(&modeMutex);
            if(time1older) {
                clock_gettime(CLOCK_MONOTONIC, &time1);
                time1long = (long)time1.tv_sec*1000000000LL + time1.tv_nsec;
                timeDelta = time1long - time2long;
            } else {
                clock_gettime(CLOCK_MONOTONIC, &time2);
                time2long = (long)time2.tv_sec*1000000000LL + time2.tv_nsec;
                timeDelta = time2long - time1long;
            }
            engine.update(timeDelta*0.0000000000005);
            break;
        case WON_MODE:
            pthread_mutex_unlock(&modeMutex);
            level++;
            importer.loadLevel(level);
            mode = SET_UP_MODE;
            break;
        default:
            pthread_mutex_unlock(&modeMutex);
            break;
        }
        pthread_mutex_lock(&stopLoopingMutex);
        if(stopLooping) {
            pthread_mutex_unlock(&stopLoopingMutex);
            return;
        }
        pthread_mutex_unlock(&stopLoopingMutex);
    }
}

void GameState::backupState()
{
    backupMarblePosition = marble.position;
}

void GameState::restoreState()
{
    marble.position = backupMarblePosition;
}
