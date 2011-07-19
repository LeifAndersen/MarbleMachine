#include "input_converter.h"

InputConverter::InputConverter(GameState & state) : state(state)
{
}

void InputConverter::move(int finger, float x, float y)
{
    // Preliminary checks
    if(finger >= MAX_FINGERS)
        return;
    fingerCoords[finger].x = x;
    fingerCoords[finger].y = y;

    // Menu button
    switch(state.menuButton.state) {
    case BUTTON_STATE_UP:
        break;
    case BUTTON_STATE_DOWN:
        break;
    case BUTTON_STATE_HOVER:
        break;
    }
}

void InputConverter::touch(int finger, float x, float y)
{
    // Preliminary checks
    if(finger >= MAX_FINGERS)
        return;
    fingerCoords[finger].x = x;
    fingerCoords[finger].y = y;

    // Menu button
    if(fingerOnButton(state.menuButton, fingerCoords[finger])) {
        state.menuButton.state = BUTTON_STATE_DOWN;
    }
}

void InputConverter::release(int finger, bool canceled)
{
    if(finger >= MAX_FINGERS)
        return;
    if(fingerOnButton(state.menuButton, fingerCoords[finger])
            && state.menuButton.state == BUTTON_STATE_DOWN) {
        pthread_mutex_lock(&state.modeMutex);
        state.mode = LEVEL_MENU_MODE;
        pthread_mutex_unlock(&state.modeMutex);
    }
}

bool InputConverter::fingerOnButton(const Button &button, vec2_t coords)
{
    // True if x and y coordinates are in range of the button.
    // to be in range, must be no less than the button/left, and no
    //     more than the top/right
    return(coords.x > button.x - button.widthHalf
           && coords.x < button.x + button.widthHalf
           && coords.y > button.y - button.heightHalf
           && coords.y > button.y + button.heightHalf);
}
