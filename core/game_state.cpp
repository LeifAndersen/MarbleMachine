#include "game_state.h"

GameState::GameState() : continueLooping(true),
    engine(*this), menu(*this), importer(*this)
{

}

GameState::~GameState()
{

}

void GameState::mainLoop()
{
    while(continueLooping) {
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
