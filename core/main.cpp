#include <pthread.h>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <cstdio>

#include "main.h"
#include "glview.h"
#include "game_state.h"
#include "os_calls.h"
#include "input_converter.h"
#include "data_importer.h"

using namespace std;

GameState state;
GLView view(state);
InputConverter converter(state);
pthread_t thread;

//Open GL events
/**
  * Called once when the program loads.  Used to set up
  * shaders and whatnot.
  */
void initGL()
{
    DataImporter::loadDrawables();
    view.initGL();
}

/**
  * Called whenever the surface has changed, and when the
  * windows is first created.  Gives the width and height
  * of the window.
  */
void updateGL(int width, int height)
{
    state.setAspectRatio(width, height);
    view.updateGL(width, height);
}

/**
  * Called when the outside code wants the screen to be
  * redrawn.  It assumes a context has already been created.
  */
void draw()
{
    view.renderFrame();
}

// Lifecycle events
/**
  * Called when the outside game wants the gamestate to be paused.
  */
void pauseGame()
{
    pthread_mutex_lock(&state.stopLoopingMutex);
    state.stopLooping = true;
    pthread_mutex_unlock(&state.stopLoopingMutex);
    pthread_join(thread, NULL);
}

void* runLoop(void * args)
{
    state.mainLoop();
    return NULL;
}

/**
  * Called when the outside game wants to start the main loop
  * of the game in another thread.
  */
void startGame()
{
    // Check to make sure another thread isn't runninng
    // if one is, you can just return,
    // otehrwise, start one up
    pthread_mutex_lock(&state.stopLoopingMutex);
    if(state.stopLooping == false) {
        pthread_mutex_unlock(&state.stopLoopingMutex);
        return;
    }
    state.stopLooping = false;
    pthread_mutex_unlock(&state.stopLoopingMutex);
    pthread_create(&thread, NULL, runLoop, NULL);
}

/**
  * Called when the game is supposed to start
  * Should not actually start the main game loop, only setup the
  * game state.  Starting the main loop will hapen on startGame().
  */
void setupGame()
{
    // Clear out any old data
    state.level = 0;
    pthread_mutex_lock(&state.planetsMutex);
    state.planets.clear();
    pthread_mutex_unlock(&state.planetsMutex);

    // Set temp mode
    pthread_mutex_lock(&state.modeMutex);
    state.mode = LEVEL_MODE;
    pthread_mutex_unlock(&state.modeMutex);

    // Set up temprorary ship
    state.ship.position.x = state.ship.position.y =
            state.ship.position.z = 0;
    state.ship.velocity.x = state.ship.velocity.y =
            state.ship.velocity.z = 0;
    state.ship.acceleration.x = state.ship.acceleration.y =
            state.ship.acceleration.z = 0;
    state.ship.rotation.x = state.ship.rotation.y =
            state.ship.rotation.z = 0;
    state.ship.radius = 1;
    state.ship.mass = 0;

    // Set up temporary planets
    pthread_mutex_lock(&state.planetsMutex);
    state.planets.push_back(Sphere());
    Sphere * planet = &state.planets.back();
    planet->mass = 5;
    planet->radius = 1;
    planet->position.x = 10;
    planet->position.y = 5;
    planet->position.z = 0;
    planet->velocity = 0.0f;

    state.planets.push_back(Sphere());
    planet = &state.planets.back();
    planet->mass = 5;
    planet->radius = 1;
    planet->position.x = -10;
    planet->position.y = 5;
    planet->position.z = 0;
    planet->velocity = 0.0f;
    pthread_mutex_unlock(&state.planetsMutex);
}

/**
  * Called to stop the game.
  * This is where anything that needs to be destructed, should be.
  */
void stopGame()
{

}

// User touch events
/**
  * Called when the user touches the screen.
  *
  * Input:
  *     Finger: is the finger number
  *         (always 0 if only 1 finger is ever used).
  *     X, Y: Coordinates on the screen of the touch
  */
void touch(int finger, float x, float y)
{
    converter.touch(finger, x, y);
}

/**
  * Called when the user moves a finger on the screen
  * he is already touching.
  *
  * Input:
  *     Finger: is the finger number
  *         (always 0 if only 1 finger is ever used).
  *     X, Y: Coordinates on the screen of the touch
  */
void move(int finger, float x, float y)
{
    converter.move(finger, x, y);
}

/**
  * Called when the user releases a finger from the screen.
  *
  * Input:
  *     Finger: is the finger number
  *     Canceled: whether or not the current gesture was canceled. (mirror's android API)
  *         (always 0 if only 1 finger is ever used).
  */
void release(int finger, bool canceled)
{
    converter.release(finger, canceled);
}
