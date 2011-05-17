#ifndef INPUT_CONVERTER_H
#define INPUT_CONVERTER_H

#include "game_state.h"

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
    Point playButton[4];
};

#endif // INPUT_CONVERTER_H