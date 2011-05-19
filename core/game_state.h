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
#include "collision_grid.h"

enum Mode { MENU_MODE, SET_UP_MODE, RUNNING_MODE, WON_MODE };

// Iterrators for convinence
typedef std::list<Plank>::iterator PlankIterator;
typedef std::list<Cannon>::iterator CannonIterator;

class GameState
{
public:
    GameState();
    ~GameState();
    void mainLoop();
    unsigned int level;

    // Player's Marble
    Sphere marble;

    // Stuff the marble can interact with
    std::list<Plank> planks;
    std::list<Cannon> cannons;

    // Goal the player is trying to get the ball to.
    Goal goal;

    // Grid for collision detection
    CollisionGrid grid;

    // Should be handeled by controller code (main.cpp).
    // contineues the main loop when true
    bool stopLooping;
    pthread_mutex_t stopLoopingMutex;

    // For what the main loop will do.
    Mode mode;
    pthread_mutex_t modeMutex;

    // For knowing how long the marble has been
    // in the cannon
    bool marbleInCannon;
    int timeInCannon;
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
