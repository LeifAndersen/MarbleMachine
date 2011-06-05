#include <cstdlib>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <pthread.h>

#include "game_state.h"
#include "os_calls.h"

GameState::GameState() : grid(FIELD_CHUNK_SIZE, FIELD_SIZE, FIELD_SIZE),
    stopLooping(true), engine(*this), menu(*this), importer(*this)
{
    // Set up mutexs
   assert(!pthread_mutex_init(&modeMutex, NULL));
   assert(!pthread_mutex_init(&stopLoopingMutex, NULL));

   // set up matrix:
   projectionMatrix.loadIdentity();
   projectionMatrix.ortho(-10.0f*aspectRatio, 10.0f*aspectRatio, -10.0f, 10.0f, -10.0f, 10.0f);
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
    log_e("Second thread started");
    while(true) {
        marble.rotation += 0.1;
        marble.radius += 0.000005;
        pthread_mutex_lock(&marble.mvMatrixMutex);
        marble.loadMVMatrix();
        //marble.mvMatrix.ortho(-10.0f, 10.0f, -10.0f, 10.0f, -10.0f, 10.0f);
        //Matrix m;
        //m.loadIdentity();
        //m.ortho(-10.0f*aspectRatio, 10.0f*aspectRatio, -10.0f, 10.0f, -10.0f, 10.0f);
        //marble.mvMatrix.perspective(10.0f, aspectRatio, -10.0f, 10.0f);
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
            engine.update(0.00005); //TODO: Get the actual time delta
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
            log_e("Second thread ended");
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
