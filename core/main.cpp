#include "gl_code.cpp" // TODO Remove this...

#include <pthread.h>

using namespace std;

//Open GL events
/**
  * Called whenever the surface has changed, and when the
  * windows is first created.  Gives the width and height
  * of the window.  Shader code should be loaded here.
  */
void init(int width, int height)
{
    setupGraphics(width, height);
}

/**
  * Called when the outside code wants the screen to be
  * redrawn.  It assumes a context has already been created.
  */
void draw()
{
    renderFrame();
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

// Music/Sound events
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

/**
  * Returns a string containting the name of
  * the music that should be playing, or the empty string
  * if nothing.
  *
  * Differes from getSound() by returning only background music.
  */
std::string getMusic()
{
    return "";
}

/**
  * Returns a string containing the name of the next sound
  * that should be played, or the empty string if no more soudns
  * need to be played.
  *
  * Will keep a queue of all the remaining sounds, and will pop each
  * element of the queue until it's empty, at which point it will return
  * an empty string.
  *
  * Differs from getMusic() by returning only sound effects which
  * need to be played.
  */
std::string getSound()
{
    return "";
}
