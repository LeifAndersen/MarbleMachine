#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <list>

#include "physics.h"
#include "menu.h"
#include "data_importer.h"
#include "sphere.h"
#include "plank.h"
#include "point.h"
#include "goal.h"
class GameState
{
public:
    GameState();
    ~GameState();
    void mainLoop();
    unsigned int level;

    // Player's Marble
    Sphere marble;

    // Planks built into the level
    std::list<Plank> levelPlanks;

    // Planks the player places
    std::list<Plank> playerPlanks;

    // Goal the player is trying to get the ball to.
    Goal goal;

    // Should be handeled by controller code (main.cpp).
    // contineues the main loop when true
    bool continueLooping;
private:
    Physics engine;
    Menu menu;
    DataImporter importer;

    // For resetting the field after the player runs the sim.
    void backupState();
    void restoreState();
    Point backupMarblePosition;

    enum State { MENU, SET_UP, RUNNING };
    State state;
};


#endif // GAME_STATE_H
