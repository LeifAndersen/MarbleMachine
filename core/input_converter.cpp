#include "input_converter.h"

InputConverter::InputConverter(GameState & state) : state(state),
    scrollingScreen(false)
{
}

void InputConverter::move(int finger, float x, float y)
{
    // Preliminary checks
    if(finger >= MAX_FINGERS)
        return;
    fingerCoords[finger].x = x;
    fingerCoords[finger].y = y;

    // Active planet
    if(state.activePlanetInUse && !state.menuOn) {
        if(state.activePlanetPlaced) {
            // Don't do anything
        } else {
            state.activePlanet.position.x = x;
            state.activePlanet.position.y = y;
        }
    }

    // Menu button
    regularButtonMove(state.menuButton, finger);

    // Menu
    if(state.menuOn) {
        if(state.musicMuted) {
            regularButtonMove(state.unMuteMusicButton, finger);
        } else {
            regularButtonMove(state.muteMusicButton, finger);
        }

        if(state.efxMuted) {
            regularButtonMove(state.unMuteEfxButton, finger);
        } else {
            regularButtonMove(state.muteEfxButton, finger);
        }
        regularButtonMove(state.quitLevelButton, finger);
        regularButtonMove(state.restartLevelButton, finger);
        return;
    }

    pthread_mutex_lock(&state.modeMutex);
    switch (state.mode) {
    case MODE_GALACTIC_MENU:
    case MODE_GALACTIC_SECTOR_MENU:
        pthread_mutex_unlock(&state.modeMutex);
        break;
    case MODE_LEVEL:
        pthread_mutex_unlock(&state.modeMutex);
        // Planet buttons
        planetButtonMove(state.lightPlanetButton, state.lightPlanets, finger,
                         LIGHT_PLANET_WEIGHT_MAX - rand() % LIGHT_PLANET_WEIGHT_VARIENCE,
                         LIGHT_PLANET_RADIUS_MAX - rand() % LIGHT_PLANET_RADIUS_VARIENCE);
        planetButtonMove(state.mediumPlanetButton, state.mediumPlanets, finger,
                         MEDIUM_PLANET_WEIGHT_MAX - rand() % MEDIUM_PLANET_WEIGHT_VARIENCE,
                         MEDIUM_PLANET_RADIUS_MAX - rand() % MEDIUM_PLANET_WEIGHT_VARIENCE);
        planetButtonMove(state.heavyPlanetButton, state.heavyPlanets, finger,
                         HEAVY_PLANET_WEIGHT_MAX - rand() % HEAVY_PLANET_WEIGHT_VARIENCE,
                         HEAVY_PLANET_RADIUS_MAX - rand() % HEAVY_PLANET_WEIGHT_VARIENCE);
        planetButtonMove(state.antiPlanetButton, state.antiPlanets, finger,
                         ANTI_PLANET_WEIGHT_MAX - rand() % ANTI_PLANET_WEIGHT_VARIENCE,
                         ANTI_PLANET_RADIUS_MAX - rand() % ANTI_PLANET_RADIUS_VARIENCE);
        break;
    case MODE_LEVEL_WON:
        pthread_mutex_unlock(&state.modeMutex);
        regularButtonMove(state.wonLevelButton, finger);
        break;
    case MODE_LEVEL_LOST:
        pthread_mutex_unlock(&state.modeMutex);
        regularButtonMove(state.lostLevelButton, finger);
        break;
    default:
        pthread_mutex_unlock(&state.modeMutex);
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

    // Active planet
    if(state.activePlanetInUse &&
            fingerOnSphere(state.activePlanet, fingerCoords[finger]) &&
            !state.menuOn) {
        if(state.activePlanetPlaced) {
            state.activePlanet.velocity.x = x;
            state.activePlanet.velocity.y = y;
            state.activePlanetSettingVelocity = true;
        } else {
            state.activePlanet.position.y = x;
            state.activePlanet.position.y = y;
        }
    }

    // Menu button
    regularButtonTouch(state.menuButton, finger);

    // Menu
    if(state.menuOn) {
        if(state.musicMuted) {
            regularButtonTouch(state.unMuteMusicButton, finger);
        } else {
            regularButtonTouch(state.muteMusicButton, finger);
        }
        if(state.efxMuted) {
            regularButtonTouch(state.unMuteEfxButton, finger);
        } else {
            regularButtonTouch(state.muteEfxButton, finger);
        }
        regularButtonTouch(state.quitLevelButton, finger);
        regularButtonTouch(state.restartLevelButton, finger);
        return;
    }

    pthread_mutex_lock(&state.modeMutex);
    switch (state.mode) {
    case MODE_GALACTIC_MENU:
    case MODE_GALACTIC_SECTOR_MENU:
        pthread_mutex_unlock(&state.modeMutex);
        break;
    case MODE_LEVEL:
        pthread_mutex_unlock(&state.modeMutex);

        // Planet buttons
        planetButtonTouch(state.lightPlanetButton, finger);
        planetButtonTouch(state.mediumPlanetButton, finger);
        planetButtonTouch(state.heavyPlanetButton, finger);
        planetButtonTouch(state.antiPlanetButton, finger);
        break;
    case MODE_LEVEL_WON:
        pthread_mutex_unlock(&state.modeMutex);
        regularButtonTouch(state.wonLevelButton, finger);
        break;
    case MODE_LEVEL_LOST:
        pthread_mutex_unlock(&state.modeMutex);
        regularButtonTouch(state.lostLevelButton, finger);
        break;
    default:
        pthread_mutex_unlock(&state.modeMutex);
        break;
    }
}

void InputConverter::release(int finger, bool canceled)
{
    // Preliminary test
    if(finger >= MAX_FINGERS)
        return;

    // Active planet
    if(state.activePlanetPlaced && state.activePlanetSettingVelocity
            && !state.menuOn) {
        if(*state.activePlanetCount > 0) {
            *state.activePlanetCount = *state.activePlanetCount - 1;
            Point offset = fingerCoords[finger];
            state.activePlanet.velocity = (offset - state.activePlanet.velocity)
                    / TOUCH_DAMPENER;
            state.activePlanet.angularVelocity.x
                    = PLANET_ROTATION - rand() % PLANET_ROTATION_VARIENT;
            state.activePlanet.angularVelocity.y
                    = PLANET_ROTATION - rand() % PLANET_ROTATION_VARIENT;
            state.activePlanet.angularVelocity.z
                    = PLANET_ROTATION - rand() % PLANET_ROTATION_VARIENT;
            state.activePlanet.angularVelocity.normalize();
            state.activePlanet.angularVelocity
                    *= PLANET_ROTATION - rand() % PLANET_ROTATION_VARIENT;
            pthread_mutex_lock(&state.planetsAddMutex);
            state.planets.push_back(state.activePlanet);
            pthread_mutex_unlock(&state.planetsAddMutex);
            state.activePlanetInUse = false;
            state.activePlanetPlaced = false;
            state.activePlanetSettingVelocity = false;
        } else {
            state.activePlanetPlaced = false;
            state.activePlanetInUse = false;
            state.activePlanetSettingVelocity = false;
        }
        return;
    }
    if(state.activePlanetInUse && !state.menuOn) {
        state.activePlanetPlaced = true;
        return;
    }

    // Menu button
    regularButtonRelease(state.menuButton, finger,
                         &InputConverter::menuButton);

    // Menu
    if(state.menuOn) {
        if(state.musicMuted) {
            regularButtonRelease(state.unMuteMusicButton, finger,
                                 &InputConverter::muteMusicButton);
        } else {
            regularButtonRelease(state.muteMusicButton, finger,
                                 &InputConverter::muteMusicButton);
        }
        if(state.efxMuted) {
            regularButtonRelease(state.unMuteEfxButton, finger,
                                 &InputConverter::muteEfxButton);
        } else {
            regularButtonRelease(state.muteEfxButton, finger,
                                 &InputConverter::muteEfxButton);
        }
        regularButtonRelease(state.quitLevelButton, finger,
                             &InputConverter::quitLevelButton);
        regularButtonRelease(state.restartLevelButton, finger,
                             &InputConverter::restartLevelButton);
        return;
    }

    unsigned int j = 1;

    pthread_mutex_lock(&state.modeMutex);
    switch(state.mode) {
    case MODE_GALACTIC_MENU:
        pthread_mutex_unlock(&state.modeMutex);

        // Iterate through the choices
        j = 1;
        for(SphereIterator i = state.planets.begin();
            i != state.planets.end() && j <= state.highestSector; i++, j++) {
            if(fingerOnSphere(*i, fingerCoords[finger])) {
                state.sector = j;
                pthread_mutex_lock(&state.modeMutex);
                state.mode = MODE_GALACTIC_SECTOR_MENU_SETUP;
                pthread_mutex_unlock(&state.modeMutex);
                return;
            }
        }
        break;
    case MODE_GALACTIC_SECTOR_MENU:
        pthread_mutex_unlock(&state.modeMutex);

        // Iterate through the choices
        if(state.sector >= state.highestSector) {
            j = 1;
            for(SphereIterator i = state.planets.begin();
                i != state.planets.end() && j <= state.highestLevel; i++, j++) {
                if(fingerOnSphere(*i, fingerCoords[finger])) {
                    state.level = j;
                    pthread_mutex_lock(&state.modeMutex);
                    state.mode = MODE_LEVEL_SETUP;
                    pthread_mutex_unlock(&state.modeMutex);
                    return;
                }
            }
        } else {
            j = 1;
            for(SphereIterator i = state.planets.begin();
                i != state.planets.end(); i++, j++) {
                if(fingerOnSphere(*i, fingerCoords[finger])) {
                    state.level = j;
                    pthread_mutex_lock(&state.modeMutex);
                    state.mode = MODE_LEVEL_SETUP;
                    pthread_mutex_unlock(&state.modeMutex);
                    return;
                }
            }
        }
        break;
    case MODE_LEVEL:
        pthread_mutex_unlock(&state.modeMutex);

        // Planet buttons
        planetButtonRelease(state.lightPlanetButton, finger);
        planetButtonRelease(state.mediumPlanetButton, finger);
        planetButtonRelease(state.heavyPlanetButton, finger);
        planetButtonRelease(state.antiPlanetButton, finger);
        break;
    case MODE_LEVEL_WON:
        pthread_mutex_unlock(&state.modeMutex);
        regularButtonRelease(state.wonLevelButton, finger,
                             &InputConverter::wonLevelButton);
        break;
    case MODE_LEVEL_LOST:
        pthread_mutex_unlock(&state.modeMutex);
        regularButtonRelease(state.lostLevelButton, finger,
                             &InputConverter::lostLevelButton);
        break;
    default:
        pthread_mutex_unlock(&state.modeMutex);
        break;
    }
}

bool InputConverter::fingerOnButton(const Button &button, const vec2_t & coords)
{
    // True if x and y coordinates are in range of the button.
    // to be in range, must be no less than the button/left, and no
    //     more than the top/right
    return(coords.x > button.x - button.widthHalf
           && coords.x < button.x + button.widthHalf
           && coords.y > button.y - button.heightHalf
           && coords.y < button.y + button.heightHalf);
}

bool InputConverter::fingerOnSphere(const Sphere &sphere, const vec2_t &coords)
{
    return(coords.x > sphere.position.x - sphere.radius
           && coords.x < sphere.position.x + sphere.radius
           && coords.y > sphere.position.y - sphere.radius
           && coords.y < sphere.position.y + sphere.radius);
}

void InputConverter::planetButtonTouch(Button &button, int finger)
{
    switch(button.state) {
    case BUTTON_STATE_UP:
    case BUTTON_STATE_HOVER:
        if(fingerOnButton(button, fingerCoords[finger])) {
            button.state = BUTTON_STATE_DOWN;
            if(!state.efxMuted)
                playSound(state.buttonSound);
        }
        break;
    case BUTTON_STATE_DOWN:
        break;
    }
}

void InputConverter::planetButtonMove(Button &button,
                                      unsigned short &planetCount, int finger,
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
            if(planetCount > 0) {
                button.state = BUTTON_STATE_UP;
                state.activePlanetInUse = true;
                state.activePlanetPlaced = false;
                state.activePlanet.position = fingerCoords[finger];
                state.activePlanet.mass = mass;
                state.activePlanet.radius = radius;
                state.activePlanet.rotation = 0.0f;
                state.activePlanet.angularVelocity.x = 0.0f;
                state.activePlanet.angularVelocity.y = 0.0f;
                state.activePlanet.angularVelocity.z = ROTATION_SPEED;
                state.activePlanetCount = &planetCount;
            }
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
            button.state = BUTTON_STATE_HOVER;
        } else {
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
    case BUTTON_STATE_HOVER:
        if(fingerOnButton(button, fingerCoords[finger])) {
            button.state = BUTTON_STATE_DOWN;
            if(!state.efxMuted)
                playSound(state.buttonSound);
        }
        break;
    case BUTTON_STATE_DOWN:
        if(fingerOnButton(button, fingerCoords[finger])) {
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
    switch(button.state) {
    case BUTTON_STATE_UP:
        break;
    case BUTTON_STATE_DOWN:
    case BUTTON_STATE_HOVER:
        if(fingerOnButton(button, fingerCoords[finger])) {
            (*this.*buttonAction)();
            button.state = BUTTON_STATE_HOVER;
        }
        break;
    }
}

void InputConverter::menuButton()
{
    pthread_mutex_lock(&state.modeMutex);
    state.menuOn = !state.menuOn;
    pthread_mutex_unlock(&state.modeMutex);
}

void InputConverter::muteEfxButton()
{
    pthread_mutex_lock(&state.soundMutex);
    state.efxMuted = !state.efxMuted;
    pthread_mutex_unlock(&state.soundMutex);
    state.importer.saveGame();
}

void InputConverter::muteMusicButton()
{
    pthread_mutex_lock(&state.soundMutex);
    state.musicMuted = !state.musicMuted;
    if(state.musicMuted) {
        stopMusic();
    } else {
        playMusic("background");
    }
    pthread_mutex_unlock(&state.soundMutex);
    state.importer.saveGame();
}

void InputConverter::quitLevelButton()
{
    pthread_mutex_lock(&state.modeMutex);
    switch(state.mode) {
    case MODE_LEVEL:
        pthread_mutex_unlock(&state.modeMutex);
        state.mode = MODE_GALACTIC_SECTOR_MENU_SETUP;
        break;
    case MODE_GALACTIC_SECTOR_MENU:
        pthread_mutex_unlock(&state.modeMutex);
        state.mode = MODE_GALACTIC_MENU_SETUP;
        break;
    case MODE_GALACTIC_MENU:
        pthread_mutex_unlock(&state.modeMutex);
        quit_game();
        break;
    case MODE_LEVEL_WON:
        pthread_mutex_unlock(&state.modeMutex);
        wonLevelButton();
        break;
    case MODE_LEVEL_LOST:
        pthread_mutex_unlock(&state.modeMutex);
        lostLevelButton();
        break;
    default:
        pthread_mutex_unlock(&state.modeMutex);
        break;
    }
}

void InputConverter::restartLevelButton()
{
    pthread_mutex_lock(&state.modeMutex);
    switch(state.mode) {
    case MODE_LEVEL:
    case MODE_LEVEL_WON:
    case MODE_LEVEL_LOST:
        state.mode = MODE_LEVEL_SETUP;
        break;
    default:
        break;
    }
    pthread_mutex_unlock(&state.modeMutex);
}

void InputConverter::wonLevelButton()
{
    // Go back to sector
    pthread_mutex_lock(&state.modeMutex);
    state.mode = MODE_GALACTIC_SECTOR_MENU_SETUP;
    pthread_mutex_unlock(&state.modeMutex);
}

void InputConverter::lostLevelButton()
{
    // restart the sector
    pthread_mutex_lock(&state.modeMutex);
    state.mode = MODE_LEVEL_SETUP;
    pthread_mutex_unlock(&state.modeMutex);
}
