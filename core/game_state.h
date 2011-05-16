#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <list>
#include <pthread.h>

#include "physics.h"
#include "menu.h"
#include "data_importer.h"
#include "sphere.h"
#include "plank.h"
#include "point.h"
#include "goal.h"
#include "cannon.h"

enum Mode { MENU, SET_UP, RUNNING };


class GameState
{
public:
    GameState();
    ~GameState();
    void mainLoop();
    unsigned int level;

    // Player's Marble
    Sphere marble;

    // Stuff built into the level
    std::list<Plank> levelPlanks;
    std::list<Cannon> levelCannons;

    // Stuff the player places
    std::list<Plank> playerPlanks;
    std::list<Cannon> playerCannons;

    // Goal the player is trying to get the ball to.
    Goal goal;

    // Should be handeled by controller code (main.cpp).
    // contineues the main loop when true
    bool stopLooping;
    pthread_mutex_t stopLoopingMutex;

    // For what the main loop will do.
    Mode mode;
    pthread_mutex_t modeMutex;
private:
    Physics engine;
    Menu menu;
    DataImporter importer;

    // For resetting the field after the player runs the sim.
    void backupState();
    void restoreState();
    Point backupMarblePosition;
};


#endif // GAME_STATE_H
