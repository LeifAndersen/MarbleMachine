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
#include "button.h"

#define GALACTIC_MENU_MODE 0
#define GALACTIC_ZONE_MENU_MODE 1
#define LEVEL_SETUP_MODE 2
#define LEVEL_MODE 3
#define LEVEL_WON_MODE 4
#define LEVEL_MENU_MODE 5

#define FONT_CHAR_SIZE 62

#define LIGHT_PLANET_WEIGHT_MAX 10
#define LIGHT_PLANET_WEIGHT_VARIENCE 2
#define MEDIUM_PLANET_WEIGHT_MAX 50
#define MEDIUM_PLANET_WEIGHT_VARIENCE 5
#define HEAVY_PLANET_WEIGHT_MAX 100
#define HEAVY_PLANET_WEIGHT_VARIENCE 10
#define ANTI_PLANET_WEIGHT_MAX -50
#define ANTI_PLANET_WEIGHT_VARIENCE -20
#define BLACK_HOLE_WEIGHT 1000

#define LIGHT_PLANET_RADIUS_MAX 10
#define LIGHT_PLANET_RADIUS_VARIENCE 2
#define MEDIUM_PLANET_RADIUS_MAX 30
#define MEDIUM_PLANET_RADIUS_VARIENCE 6
#define HEAVY_PLANET_RADIUS_MAX 50
#define HEAVY_PLANET_RADIUS_VARIENCE 10
#define ANTI_PLANET_RADIUS_MAX 50
#define ANTI_PLANET_RADIUS_VARIENCE 20
#define BLACK_HOLE_RADIUS 100
#define RADIUS_OFFSET 10 // Because we need the radius opperators in a mod function.

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
    MMTEX * tex0;

    // Planets (and asteroids)
    std::list<Sphere> planets;
    pthread_mutex_t planetsMutex;
    std::vector<DrawablePoint> planetVerts;
    std::vector<GLushort> planetIndices;
    std::vector<DrawablePoint> antiPlanetVerts;
    std::vector<GLushort> antiPlanetIndices;


    // Goal the player is trying to get the ball to.
    Sphere goal;

    // Should be handeled by controller code (main.cpp).
    // contineues the main loop when true
    bool stopLooping;
    pthread_mutex_t stopLoopingMutex;

    // For what the main loop will do.
    unsigned int mode;
    pthread_mutex_t modeMutex;

    // Buttons
    Button menuButton;
    Button lightPlanetButton;
    Button mediumPlanetButton;
    Button heavyPlanetButton;
    Button antiPlanetButton;

    // a-z 0-25
    // A-Z 26-51
    // 0-9 52-61
    button_verts_t font_chars[FONT_CHAR_SIZE];

    // Menu Buttons
    Button restartLevelButton;
    Button muteButton;

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
