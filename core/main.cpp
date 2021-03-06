#include <pthread.h>
#include <cstdlib>
#include <cassert>

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
    state.importer.loadDrawables();
    state.importer.loadTextures();
    state.importer.loadSounds();
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
    if(!state.musicMuted) {
        stopMusic();
    }
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
    if(!state.musicMuted) {
        playMusic("background");
    }
}

/**
  * Called when the game is supposed to start
  * Should not actually start the main game loop, only setup the
  * game state.  Starting the main loop will hapen on startGame().
  */
void setupGame()
{
    // Clear out any old data
    state.importer.loadGame();
}

/**
  * Called to stop the game.
  * This is where anything that needs to be destructed, should be.
  */
void stopGame()
{
    state.importer.unloadTextures();
    state.importer.unloadSounds();
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
    converter.touch(finger, x*WIDTH, y*WIDTH/state.aspectRatio);
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
    converter.move(finger, x*WIDTH, y*WIDTH/state.aspectRatio);
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

// Misc events
/**
  * Toggle the menu for the game.
  */
void toggleMenu()
{
    pthread_mutex_lock(&state.modeMutex);
    state.menuOn = !state.menuOn;
    pthread_mutex_unlock(&state.modeMutex);
    return;
}

/**
  * Tells the game to go back to the previous place.
  * If in a level, go to sector, then galaxy, quit, etc.
  */
void goBack()
{
    converter.quitLevelButton();
}
