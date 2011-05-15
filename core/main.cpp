#include <pthread.h>

#include "main.h"
#include "glview.h"
#include "game_state.h"
#include "os_calls.h"

using namespace std;

GLView view;
GameState state;

//Open GL events
/**
  * Called once when the program loads.  Used to set up
  * shaders and whatnot.
  */
void initGL()
{
    // Do nothing for now
}

/**
  * Called whenever the surface has changed, and when the
  * windows is first created.  Gives the width and height
  * of the window.
  */
void updateGL(int width, int height)
{
    view.updateGL(width, height);
    int sound = loadSound("wilhelm_scream");
    if(sound != 0)
        sleep(1);
        playSound(sound);
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
void resumeGame()
{
    pthread_mutex_lock(&state.stopLoopingMutex);
    if(state.stopLooping == false) {
        pthread_mutex_unlock(&state.stopLoopingMutex);
        return;
    }
    state.stopLooping = false;
    pthread_mutex_unlock(&state.stopLoopingMutex);
    pthread_t thread;
    pthread_create(&thread, NULL, runLoop, NULL);
    pthread_detach(thread);
}

/**
  * Called when the outside game wants the game to reset itself.
  */
void resetGame()
{

}

/**
  * Called when the game is supposed to start
  * Should not actually start the main game loop, only setup the
  * game state.  Starting the main loop will hapen on resumeGame().
  */
void startGame()
{

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

}

// Touch events
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

}
