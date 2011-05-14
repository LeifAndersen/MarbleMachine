#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "physics.h"
#include "menu.h"

class GameState
{
public:
    GameState();
private:
    Physics engine;
    Menu menu;

    /**
      * For resetting the field after the player runs the sim.
      */
    GameState * backup;
    void backupState();
    void restoreState();
};


#endif // GAME_STATE_H
