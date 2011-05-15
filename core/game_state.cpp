#include "game_state.h"

GameState::GameState() : continueLooping(false),
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
            break;
        default:
            break;
        }
        pthread_mutex_lock(&continueLoopingMutex);
        if(!continueLooping) {
            pthread_mutex_unlock(&continueLoopingMutex);
            return;
        }
        pthread_mutex_unlock(&continueLoopingMutex);
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
