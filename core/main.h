#ifndef MAIN_H
#define MAIN_H

//Open GL events
/**
  * Called whenever the surface has changed, and when the
  * windows is first created.  Gives the width and height
  * of the window.  Shader code should be loaded here.
  */
void init(int width, int height);

/**
  * Called when the outside code wants the screen to be
  * redrawn.  It assumes a context has already been created.
  */
void draw();

// Lifecycle events
/**
  * Called when the outside game wants the gamestate to be paused.
  */
void pause();

/**
  * Called when the outside game wants to resume a paused game.
  */
void resume();

/**
  * Called when the outside game wants the game to reset itself.
  */
void reset();


// User touch events
/**
  * Called when the user touches the screen.
  *
  * Input:
  *     Finger: is the finger number
  *         (always 0 if only 1 finger is ever used).
  *     X, Y: Coordinates on the screen of the touch
  */
void touch(int finger, int x, int y);

/**
  * Called when the user moves a finger on the screen
  * he is already touching.
  *
  * Input:
  *     Finger: is the finger number
  *         (always 0 if only 1 finger is ever used).
  *     X, Y: Coordinates on the screen of the touch
  */
void move(int finger, int x, int y);

/**
  * Called when the user releases a finger from the screen.
  *
  * Input:
  *     Finger: is the finger number
  *         (always 0 if only 1 finger is ever used).
  */
void release(int finger);

#endif // MAIN_H
