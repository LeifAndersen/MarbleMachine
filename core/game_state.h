#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <list>
#include <pthread.h>
#include <string>

#include "os_calls.h"
#include "physics.h"
#include "data_importer.h"
#include "sphere.h"
#include "point.h"
#include "goal.h"
#include "button.h"

#define WIDTH 100.0f

#define MODE_GALACTIC_MENU_SETUP 0
#define MODE_GALACTIC_MENU 1
#define MODE_GALACTIC_SECTOR_MENU  2
#define MODE_GALACTIC_SECTOR_MENU_SETUP 3
#define MODE_LEVEL_SETUP 4
#define MODE_LEVEL 5
#define MODE_LEVEL_WON 6

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

    // Level data
    unsigned int level;
    unsigned int sector;
    std::string levelName;
    std::string sectorName;
    unsigned int highestLevel;
    unsigned int highestSector;
    unsigned int levelsInSector;
    unsigned int sectorsInGalaxy;

    // For those pieces of data which need a mutex, but aren't
    // written to much.
    pthread_mutex_t miscMutex;

    // Aspect ratio of the window (for matrix magic)
    void setAspectRatio(float width, float height);

    // For turning it into projection coordinates
    Matrix projectionMatrix;

    // The ship
    Sphere ship;
    std::vector<DrawablePoint> shipVerts;
    std::vector<GLushort> shipIndices;
    MMTEX * tex0;

    // Planets, also used for levels in menu
    std::list<Sphere> planets;
    pthread_mutex_t planetsMutex;
    std::vector<DrawablePoint> lightPlanetVerts;
    std::vector<GLushort> lightPlanetIndices;
    std::vector<DrawablePoint> mediumPlanetVerts;
    std::vector<GLushort> mediumPlanetIndices;
    std::vector<DrawablePoint> heavyPlanetVerts;
    std::vector<GLushort> heavyPlanetIndices;
    std::vector<DrawablePoint> antiPlanetVerts;
    std::vector<GLushort> antiPlanetIndices;
    std::vector<DrawablePoint> blackHoleVerts;
    std::vector<GLushort> blackHoleIndices;
    std::vector<Sphere> pendingPlanets;
    std::vector<DrawablePoint> arrowVerts;
    std::vector<GLushort> arrowIndices;
    
    unsigned short lightPlanets;
    unsigned short mediumPlanets;
    unsigned short heavyPlanets;
    unsigned short antiPlanets;


    // Goal the player is trying to get the ball to.
    Sphere goal;
    std::vector<DrawablePoint> goalVerts;
    std::vector<GLushort> goalIndices;

    // Should be handeled by controller code (main.cpp).
    // contineues the main loop when true
    bool stopLooping;
    pthread_mutex_t stopLoopingMutex;

    // For what the main loop will do.
    unsigned int mode;
    pthread_mutex_t modeMutex;

    // For the GLview, to see if there's new data to be loaded onto GPU
    bool dataNeedsLoading;
    pthread_mutex_t dataLoadingMutex;

    // Buttons
    Button menuButton;
    Button lightPlanetButton;
    Button mediumPlanetButton;
    Button heavyPlanetButton;
    Button antiPlanetButton;
    Button wonLevelButton;

    // a-z 0-25
    // A-Z 26-51
    // 0-9 52-61
    button_verts_t font_chars[FONT_CHAR_SIZE];

    // Menu Buttons
    Button restartLevelButton;
    Button quitLevelButton;
    Button muteMusicButton;
    Button unMuteMusicButton;
    Button muteEfxButton;
    Button unMuteEfxButton;

    DataImporter importer;

    bool menuOn;
    bool musicMuted;
    bool efxMuted;
    pthread_mutex_t soundMutex;

    // Background for the zone
    button_verts_t background;
private:
    Physics engine;

    // Aspect ratio
    float aspectRatio;

    // For time deltas
    MMTIMER * timer;
};


#endif // GAME_STATE_H
