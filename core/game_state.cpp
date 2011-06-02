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
   assert(!pthread_mutex_init(&modeMutex, NULL));
   assert(!pthread_mutex_init(&stopLoopingMutex, NULL));
}

GameState::~GameState()
{

}

void GameState::mainLoop()
{
    log_e("Second thread started");
    while(true) {
        pthread_mutex_lock(&marble.mvMatrixMutex);
        marble.loadMVMatrix();
        marble.mvMatrix.ortho(-10.0f, 10.0f, -10.0f, 10.0f, -10.0f, 10.0f);
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
            engine.update(1); //TODO: Get the actual time delta
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
            log_e("Second thread ended");
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
