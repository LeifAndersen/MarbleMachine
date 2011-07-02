#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <list>
#include <pthread.h>

#include "os_calls.h"
#include "physics.h"
#include "menu.h"
#include "data_importer.h"
#include "sphere.h"
#include "point.h"
#include "goal.h"

#define GALACTIC_MENU_MODE 0
#define GALACTIC_ZONE_MENU_MODE 1
#define LEVEL_SETUP_MODE 2
#define LEVEL_MODE 3
#define LEVEL_WON_MODE 4

typedef std::list<Sphere>::iterator SphereIterator;

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

    // The ship
    Sphere ship;
    std::vector<DrawablePoint> shipVerts;
    std::vector<GLushort> shipIndices;
    std::vector<DrawableColor> tex0;

    // Planets (and asteroids)
    std::list<Sphere> planets;
    pthread_mutex_t planetsMutex;
    std::vector<DrawablePoint> planetVerts;
    std::vector<GLushort> planetIndices;
    std::vector<DrawablePoint> antiPlanetVerts;
    std::vector<GLushort> antiPlanetIndices;


    // Goal the player is trying to get the ball to.
    Goal goal;

    // Should be handeled by controller code (main.cpp).
    // contineues the main loop when true
    bool stopLooping;

    pthread_mutex_t stopLoopingMutex;

    // For what the main loop will do.
    unsigned int mode;
    pthread_mutex_t modeMutex;

    DataImporter importer;

private:
    Physics engine;
    Menu menu;
    // Aspect ratio
    float aspectRatio;

    // For time deltas
    MMTIMER * timer;
};


#endif // GAME_STATE_H
