#include "game_state.h"

GameState::GameState() : engine(*this), menu(*this), importer(*this)
{

}

GameState::~GameState()
{

}

void GameState::mainLoop()
{

}

void GameState::backupState()
{
    backupMarblePosition = marble.position;
}

void GameState::restoreState()
{
    marble.position = backupMarblePosition;
}
