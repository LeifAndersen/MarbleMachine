#include "game_state.h"

GameState::GameState() : stopLooping(true),
    engine(*this), menu(*this), importer(*this)
{

}

GameState::~GameState()
{

}

void GameState::mainLoop()
{
    while(true) {
        pthread_mutex_lock(&modeMutex);
        switch(mode) {
        case MENU:
            pthread_mutex_unlock(&modeMutex);
            break;
        case SET_UP:
            pthread_mutex_unlock(&modeMutex);
            break;
        case RUNNING:
            pthread_mutex_unlock(&modeMutex);
            engine.update();
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
