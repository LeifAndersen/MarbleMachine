#include "game_state.h"
#include <android/log.h>

GameState::GameState() : level(0), grid(0, 0, 0), stopLooping(true),
    marbleInCannon(false), timeInCannon(0), engine(*this),
    menu(*this), importer(*this)
{
    importer.loadDrawables();
    objLoader loader;
    __android_log_print(ANDROID_LOG_ERROR, "gamestate",  "Got here!");
}

GameState::~GameState()
{

}

void GameState::mainLoop()
{
    while(true) {
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
