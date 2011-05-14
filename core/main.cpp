#include "include_opengl.h"
#include "os_calls.h"


#include <pthread.h>
#include "main.h"
#include "glview.h"
#include "game_state.h"
#include "physics.h"
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

}

/**
  * Called when the outside game wants to resume a paused game.
  */
void resumeGame()
{

}

/**
  * Called when the outside game wants the game to reset itself.
  */
void resetGame()
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
void touch(int finger, int x, int y)
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
void move(int finger, int x, int y)
{

}

/**
  * Called when the user releases a finger from the screen.
  *
  * Input:
  *     Finger: is the finger number
  *         (always 0 if only 1 finger is ever used).
  */
void release(int finger)
{

}
