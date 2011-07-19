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
        if(fingerOnButton(state.menuButton, fingerCoords[finger])) {
            state.menuButton.state = BUTTON_STATE_HOVER;
        }
        break;
    case BUTTON_STATE_DOWN:
        if(fingerOnButton(state.menuButton, fingerCoords[finger])) {
        } else {
            state.menuButton.state = BUTTON_STATE_UP;
        }
        break;
    case BUTTON_STATE_HOVER:
        if(fingerOnButton(state.menuButton, fingerCoords[finger])) {
        } else {
            state.menuButton.state = BUTTON_STATE_UP;
        }
        break;
    }

    // Planet buttons
    planetButtonMove(state.lightPlanetButton, finger,
                     LIGHT_PLANET_WEIGHT_MAX - rand() % LIGHT_PLANET_WEIGHT_VARIENCE,
                     LIGHT_PLANET_RADIUS_MAX - rand() % LIGHT_PLANET_RADIUS_VARIENCE);
    planetButtonMove(state.mediumPlanetButton, finger,
                     MEDIUM_PLANET_WEIGHT_MAX - rand() % MEDIUM_PLANET_WEIGHT_VARIENCE,
                     MEDIUM_PLANET_RADIUS_MAX - rand() % MEDIUM_PLANET_WEIGHT_VARIENCE);
    planetButtonMove(state.heavyPlanetButton, finger,
                     HEAVY_PLANET_WEIGHT_MAX - rand() % HEAVY_PLANET_WEIGHT_VARIENCE,
                     HEAVY_PLANET_RADIUS_MAX - rand() % HEAVY_PLANET_WEIGHT_VARIENCE);
    planetButtonMove(state.antiPlanetButton, finger,
                     ANTI_PLANET_WEIGHT_MAX - rand() % ANTI_PLANET_WEIGHT_VARIENCE,
                     ANTI_PLANET_RADIUS_MAX - rand() % ANTI_PLANET_RADIUS_VARIENCE);
}

void InputConverter::touch(int finger, float x, float y)
{
    // Preliminary checks
    if(finger >= MAX_FINGERS)
        return;
    fingerCoords[finger].x = x;
    fingerCoords[finger].y = y;

    // Menu button
    switch(state.menuButton.state) {
    case BUTTON_STATE_UP:
        if(fingerOnButton(state.menuButton, fingerCoords[finger])) {
            state.menuButton.state = BUTTON_STATE_DOWN;
        }
        break;
    case BUTTON_STATE_DOWN:
        if(fingerOnButton(state.menuButton, fingerCoords[finger])) {
        }
        break;
    case BUTTON_STATE_HOVER:
        if(fingerOnButton(state.menuButton, fingerCoords[finger])) {
            state.menuButton.state = BUTTON_STATE_DOWN;
        }
        break;
    }

    // Planet buttons
    planetButtonTouch(state.lightPlanetButton, finger);
    planetButtonTouch(state.mediumPlanetButton, finger);
    planetButtonTouch(state.heavyPlanetButton, finger);
    planetButtonTouch(state.antiPlanetButton, finger);
}

void InputConverter::release(int finger, bool canceled)
{
    // Preliminary test
    if(finger >= MAX_FINGERS)
        return;

    // Menu button
    switch(state.menuButton.state) {
    case BUTTON_STATE_UP:
        break;
    case BUTTON_STATE_DOWN:
        if(fingerOnButton(state.menuButton, fingerCoords[finger])) {
            pthread_mutex_lock(&state.modeMutex);
            if(state.mode == LEVEL_MODE) {
                state.mode = LEVEL_MENU_MODE;
            } else if(state.mode == LEVEL_MENU_MODE) {
                state.mode = LEVEL_MODE;
            }
            pthread_mutex_unlock(&state.modeMutex);
        }
        break;
    case BUTTON_STATE_HOVER:
        break;
    }

    // Planet buttons
    planetButtonRelease(state.lightPlanetButton, finger);
    planetButtonRelease(state.mediumPlanetButton, finger);
    planetButtonRelease(state.heavyPlanetButton, finger);
    planetButtonRelease(state.antiPlanetButton, finger);
}

bool InputConverter::fingerOnButton(const Button &button, const vec2_t & coords)
{
    // True if x and y coordinates are in range of the button.
    // to be in range, must be no less than the button/left, and no
    //     more than the top/right
    return(coords.x > button.x - button.widthHalf
           && coords.x < button.x + button.widthHalf
           && coords.y > button.y - button.heightHalf
           && coords.y > button.y + button.heightHalf);
}

void InputConverter::planetButtonTouch(const Button &button, int finger)
{
    switch(button.state) {
    case BUTTON_STATE_UP:
    case BUTTON_STATE_HOVER:
        if(fingerOnButton(button, fingers[finger])) {
            button.state = BUTTON_STATE_DOWN;
        }
        break;
    case BUTTON_STATE_DOWN:
        break;
    }
}

void InputConverter::planetButtonMove(const Button &button, int finger,
                                      float mass, float radius)
{
    switch(button.state) {
    case BUTTON_STATE_UP:
        if(fingerOnButton(button, finger)) {
            button.state = BUTTON_STATE_HOVER;
        }
        break;
    case BUTTON_STATE_DOWN:
        if(fingerOnButton(button, finger)) {

        } else {
            button.state = BUTTON_STATE_UP;
            // Make planet
        }
        break;
    case BUTTON_STATE_HOVER:
        if(fingerOnButton(button, finger)) {

        } else {
            button.state = BUTTON_STATE_UP;
        }
        break;
    }
}

void InputConverter::planetButtonRelease(const Button &button, int finger)
{
    switch(button.state) {
    case BUTTON_STATE_UP:
        break;
    case BUTTON_STATE_DOWN:
        if(fingerOnButton(button, fingers[finger])) {
            button.state = BUTTON_STATE_UP;
        }
        break;
    case BUTTON_STATE_HOVER:
        break;
    }
}
