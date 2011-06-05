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

#define MARBLE_RADIUS 1
#define FIELD_SIZE 1000
#define FIELD_CHUNK_SIZE 100
// FIELD_CHUNK_SIZE >= MARBLE_RADIUS!!!

#define MENU_MODE 0
#define SET_UP_MODE 1
#define RUNNING_MODE 2
#define WON_MODE 3

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

    // Aspect ratio of the window (for matrix magic)
    void setAspectRatio(float width, float height);

    // For turning it into projection coordinates
    Matrix projectionMatrix;

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
    unsigned int mode;
    pthread_mutex_t modeMutex;

    // For knowing how long the marble has been
    // in the cannon
    bool marbleInCannon;
    float timeInCannon;
    Cannon * firingCannon;

    static const int CANNON_FIRE_TIME = 25;
    static const int CANNON_FIRE_VELOCITY = 25;

private:
    Physics engine;
    Menu menu;
    DataImporter importer;

    // Aspect ratio
    float aspectRatio;

    // For resetting the field after the player runs the sim.
    void backupState();
    void restoreState();
    Point backupMarblePosition;
};


#endif // GAME_STATE_H
