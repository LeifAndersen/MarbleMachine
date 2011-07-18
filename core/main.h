#ifndef MAIN_H
#define MAIN_H

//Open GL events
/**
  * Called once when the program loads.  Used to set up
  * shaders and whatnot.
  */
void initGL();

/**
  * Called whenever the surface has changed, and when the
  * windows is first created.  Gives the width and height
  * of the window.
  */
void updateGL(int width, int height);

/**
  * Called when the outside code wants the screen to be
  * redrawn.  It assumes a context has already been created.
  */
void draw();

// Lifecycle events
/**
  * Called when the outside game wants the gamestate to be paused.
  */
void pauseGame();

/**
  * Called when the outside game wants to start the main loop
  * of the game in another thread.
  */
void startGame();

/**
  * Called when the game is supposed to start
  * Should not actually start the main game loop, only setup the
  * game state.  Starting the main loop will hapen on startGame().
  */
void setupGame();

/**
  * Called to stop the game.
  * This is where anything that needs to be destructed, should be.
  */
void stopGame();

// User touch events
/**
  * Called when the user touches the screen.
  *
  * Input:
  *     Finger: is the finger number
  *         (always 0 if only 1 finger is ever used).
  *     X, Y: Coordinates on the screen of the touch, between -1 and 1,
  *            -1 is button and left
  */
void touch(int finger, float x, float y);

/**
  * Called when the user moves a finger on the screen
  * he is already touching.
  *
  * Input:
  *     Finger: is the finger number
  *         (always 0 if only 1 finger is ever used).
  *     X, Y: Coordinates on the screen of the touch, between -1 and 1,
  *            -1 is button and left
  */
void move(int finger, float x, float y);

/**
  * Called when the user releases a finger from the screen.
  *
  * Input:
  *     Finger: is the finger number
  *     Canceled: whether or not the current gesture was canceled. (mirror's android API)
  *         (always 0 if only 1 finger is ever used).
  */
void release(int finger, bool canceled);

// Misc events
/**
  * Toggle the menu for the game.
  */
void toggleMenu();

#endif // MAIN_H
