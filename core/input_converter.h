#ifndef INPUT_CONVERTER_H
#define INPUT_CONVERTER_H

#include "game_state.h"
#include "point.h"

#define MAX_FINGERS 1

class InputConverter
{
public:
    InputConverter(GameState & state);

    /**
      * Called when the user touches the screen.
      *
      * Input:
      *     Finger: is the finger number
      *         (always 0 if only 1 finger is ever used).
      *     X, Y: Coordinates on the screen of the touch
      */
    void touch(int finger, float x, float y);

    /**
      * Called when the user moves a finger on the screen
      * he is already touching.
      *
      * Input:
      *     Finger: is the finger number
      *         (always 0 if only 1 finger is ever used).
      *     X, Y: Coordinates on the screen of the touch
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
private:
    GameState & state;
    vec2_t fingerCoords[MAX_FINGERS];
    bool scrollingScreen;

    /**
      * Determin if the mouse is on top of the button.
      *
      * Input:
      *    Button: The button in question
      *    x:      The x-coord of the mouse
      *    y:      The y-coord of the mosue
      *
      * Output: True if the mouse is over the button.
      */
    static bool fingerOnButton(const Button & button, const vec2_t & coords);

    /**
      * Checks to see if your finger has touched the sphere
      *      uses a square approcimation.
      *
      * Input
      *    Sphere: The sphere you're testing
      *    x:      The x coord of the finger
      *    y:      The y coord of the finger
      */
    static bool fingerOnSphere(const Sphere & sphere, const vec2_t & coords);

    /**
      * Called on each planet button when a finger is pressed.
      */
    void planetButtonTouch(Button & button, int finger);


    /**
      * Called on each planet button when a finger is moved, can create a new
      * planet.
      */
    void planetButtonMove(Button & button, unsigned short & planetCount,
                          int finger, float mass, float radius);

    /**
      * Called on each planet button when a finger is released.
      */
    void planetButtonRelease(Button & button, int finger);

    /**
      * Called on every button when a finger is put down.
      */
    void regularButtonTouch(Button & button, int finger);

    /**
      * Called on every button when a finger is moved.
      */
    void regularButtonMove(Button & button, int finger);

    /**
      * Called on every button when the finger is released.
      */
    void regularButtonRelease(Button & button, int finger,
                              void (InputConverter::*buttonAction)());

    // These are buttons for the various button functions (listed aboive)
    void menuButton();
    void restartLevelButton();
    void muteMusicButton();
    void muteEfxButton();
public:
    void quitLevelButton();
    void wonLevelButton();
    void lostLevelButton();
private:
};

#endif // INPUT_CONVERTER_H
