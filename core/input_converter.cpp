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
    regularButtonMove(state.menuButton, finger);

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
    regularButtonTouch(state.menuButton, finger);

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
    regularButtonRelease(state.menuButton, finger,
                         &InputConverter::menuButton);

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

void InputConverter::planetButtonTouch(Button &button, int finger)
{
    switch(button.state) {
    case BUTTON_STATE_UP:
    case BUTTON_STATE_HOVER:
        if(fingerOnButton(button, fingerCoords[finger])) {
            button.state = BUTTON_STATE_DOWN;
        }
        break;
    case BUTTON_STATE_DOWN:
        break;
    }
}

void InputConverter::planetButtonMove(Button &button, int finger,
                                      float mass, float radius)
{
    switch(button.state) {
    case BUTTON_STATE_UP:
        if(fingerOnButton(button, fingerCoords[finger])) {
            button.state = BUTTON_STATE_HOVER;
        }
        break;
    case BUTTON_STATE_DOWN:
        if(fingerOnButton(button, fingerCoords[finger])) {

        } else {
            button.state = BUTTON_STATE_UP;
            // Make planet
        }
        break;
    case BUTTON_STATE_HOVER:
        if(fingerOnButton(button, fingerCoords[finger])) {

        } else {
            button.state = BUTTON_STATE_UP;
        }
        break;
    }
}

void InputConverter::planetButtonRelease(Button &button, int finger)
{
    switch(button.state) {
    case BUTTON_STATE_UP:
        break;
    case BUTTON_STATE_DOWN:
        if(fingerOnButton(button, fingerCoords[finger])) {
            button.state = BUTTON_STATE_UP;
        }
        break;
    case BUTTON_STATE_HOVER:
        break;
    }
}

void InputConverter::regularButtonTouch(Button &button, int finger)
{
    switch(button.state) {
    case BUTTON_STATE_UP:
        if(fingerOnButton(button, fingerCoords[finger])) {
            button.state = BUTTON_STATE_DOWN;
        }
        break;
    case BUTTON_STATE_DOWN:
        if(fingerOnButton(button, fingerCoords[finger])) {
        }
        break;
    case BUTTON_STATE_HOVER:
        if(fingerOnButton(button, fingerCoords[finger])) {
            button.state = BUTTON_STATE_DOWN;
        }
        break;
    }
}

void InputConverter::regularButtonMove(Button &button, int finger)
{
    switch(button.state) {
    case BUTTON_STATE_UP:
        if(fingerOnButton(button, fingerCoords[finger])) {
            button.state = BUTTON_STATE_HOVER;
        }
        break;
    case BUTTON_STATE_DOWN:
        if(fingerOnButton(button, fingerCoords[finger])) {
        } else {
            button.state = BUTTON_STATE_UP;
        }
        break;
    case BUTTON_STATE_HOVER:
        if(fingerOnButton(button, fingerCoords[finger])) {
        } else {
            button.state = BUTTON_STATE_UP;
        }
        break;
    }
}

void InputConverter::regularButtonRelease(Button &button, int finger,
                                          void (InputConverter::*buttonAction)())
{
    switch(state.menuButton.state) {
    case BUTTON_STATE_UP:
        break;
    case BUTTON_STATE_DOWN:
        if(fingerOnButton(state.menuButton, fingerCoords[finger])) {
            (*this.*buttonAction)();
        }
        break;
    case BUTTON_STATE_HOVER:
        if(fingerOnButton(button, fingerCoords[finger])) {
        } else {
            button.state = BUTTON_STATE_UP;
        }
        break;
    }
}

void InputConverter::menuButton()
{
    pthread_mutex_lock(&state.modeMutex);
    if(state.mode == MODE_LEVEL) {
        state.mode = MODE_LEVEL_MENU;
    } else if(state.mode == MODE_LEVEL_MENU) {
        state.mode = MODE_LEVEL;
    }
    pthread_mutex_unlock(&state.modeMutex);
}

void InputConverter::muteEfxButton()
{
    pthread_mutex_lock(&state.soundMutex);
    if(state.efxMuted) {
        state.efxMuted = false;
        state.muteEfxButton.buttonOnScreen = false;
        state.unMuteEfxButton.buttonOnScreen = true;
    } else {
        state.efxMuted = true;
        state.muteEfxButton.buttonOnScreen = true;
        state.unMuteEfxButton.buttonOnScreen = false;
    }
    pthread_mutex_unlock(&state.soundMutex);
}

void InputConverter::muteMusicButton()
{
    pthread_mutex_lock(&state.soundMutex);
    if(state.musicMuted) {
        state.musicMuted = false;
        state.muteMusicButton.buttonOnScreen = false;
        state.unMuteMusicButton.buttonOnScreen = true;
    } else {
        state.efxMuted = true;
        state.muteMusicButton.buttonOnScreen = true;
        state.unMuteMusicButton.buttonOnScreen = false;
    }
    pthread_mutex_unlock(&state.soundMutex);
}

void InputConverter::quitLevelButton()
{
    pthread_mutex_lock(&state.modeMutex);
    switch(state.mode) {
    case MODE_LEVEL:
    case MODE_LEVEL_WON:
    case MODE_LEVEL_MENU:
        state.mode = MODE_GALACTIC_ZONE_MENU;
        break;
    case MODE_GALACTIC_ZONE_MENU:
        state.mode = MODE_GALACTIC_MENU;
        break;
    }
    pthread_mutex_unlock(&state.modeMutex);
}

void InputConverter::restartLevelButton()
{
    pthread_mutex_lock(&state.modeMutex);
    switch(state.mode) {
    case MODE_LEVEL:
    case MODE_LEVEL_MENU:
        state.mode = MODE_LEVEL_SETUP;
        break;
    }
    pthread_mutex_unlock(&state.modeMutex);
}
