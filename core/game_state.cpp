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
        switch(state) {
        case MENU:
            break;
        case SET_UP:
            break;
        case RUNNING:
            engine.update();
            break;
        default:
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
