#include <list>
#include <cstdlib>
#include <cmath>

#include "physics.h"
#include "game_state.h"
#include "os_calls.h"

#define M_G 0.1f //6.67428E-11
#define SHIP_G 1000.0f
#define RAND_VAR_CHANGE 10
#define HALF_RAND_VAR_CHANGE 5

using namespace std;

Physics::Physics(GameState & state) : state(state)
{
}

void Physics::update(float timeDelta)
{
    // Get local references for speed
    Sphere & ship = state.ship;
    Sphere & goal = state.goal;
    Sphere * planet;
    Point distance;
    float mag;
    float magsquared;
    float pull;
    unsigned int randNum;

    // Make sure to use whatever parts of the equation possible twice
    // (namely effecting both planets).

    // Run the acceleration equations on every planet/asteroid
    for(SphereIterator i = state.planets.begin(); i != state.planets.end(); i++) {

        bool collision = false;

        // Planet - Planet
        for(SphereIterator j = i; j != state.planets.end(); j++) {
            if(i == j)
                continue;

            // First move the planets
            distance = i->position - j->position;
            magsquared = distance.magnitudeSquared();
            mag = sqrtf(magsquared);
            pull = M_G/magsquared;
            distance /= mag;
            i->acceleration -= distance*pull*j->mass;
            j->acceleration += distance*pull*i->mass;

            // Next do colisions:
            if(mag < i->radius + j->radius) {

                pthread_mutex_lock(&state.planetsMutex);
                // Add in some new, smaller, planets
                // temporarily just 4, make it a bit more random later.
                randNum = rand() % ((unsigned int)(fabsf(i->mass))+1);
                for(unsigned int k = 0; k < randNum; k++) {
                    state.planets.push_back(Sphere());
                    planet = &state.planets.back();
                    planet->acceleration = 0.0f;
                    planet->velocity = (j->velocity*-1) +
                            Point(((rand() % RAND_VAR_CHANGE) - HALF_RAND_VAR_CHANGE),
                                   ((rand() % RAND_VAR_CHANGE) - HALF_RAND_VAR_CHANGE),
                                   0);
                    planet->position = (j->position) +
                            Point(((rand() % RAND_VAR_CHANGE)),
                                  ((rand() % RAND_VAR_CHANGE)),
                                  0);
                    planet->mass = i->mass/randNum;
                    planet->radius = i->radius/randNum;
                }

                randNum = rand() % ((unsigned int)(fabsf(j->mass))+1);
                for(unsigned int k = 0; k < randNum; k++) {
                    state.planets.push_back(Sphere());
                    planet = &state.planets.back();
                    planet->acceleration = 0.0f;
                    planet->velocity = (j->velocity*-1) +
                            Point(((rand() % RAND_VAR_CHANGE) - HALF_RAND_VAR_CHANGE),
                                   ((rand() % RAND_VAR_CHANGE) - HALF_RAND_VAR_CHANGE),
                                   0);
                    planet->position = (j->position) +
                            Point(((rand() % RAND_VAR_CHANGE)),
                                  ((rand() % RAND_VAR_CHANGE)),
                                  0);
                    planet->mass = j->mass/randNum;
                    planet->radius = j->radius/randNum;
                }

                // Delete the old planets
                state.planets.erase(j);
                state.planets.erase(i--);
                pthread_mutex_unlock(&state.planetsMutex);
                collision = true;
                break;
            }
        }

        if(collision)
            continue;

        // Planet - Ship
        // First move the planets
        distance = i->position - ship.position;
        magsquared = distance.magnitudeSquared();
        mag = sqrtf(magsquared);
        pull = M_G/magsquared;
        distance /= mag;
        i->acceleration -= distance*pull*ship.mass;
        ship.acceleration += distance*pull*i->mass*SHIP_G;

        // Next do colisions:
        if(mag < i->radius + ship.radius) {
            pthread_mutex_lock(&state.modeMutex);
            state.mode = MODE_LEVEL_LOST;
            pthread_mutex_unlock(&state.modeMutex);
            return;
        }

        // Finally move the asteroid
        i->velocity += i->acceleration * timeDelta;
        i->position += i->velocity * timeDelta;

        // And reset the acceleration for the next go arround
        i->acceleration = 0.0f;
    }

    // Check Ship - goal colision
    distance = goal.position - ship.position;
    magsquared = distance.magnitudeSquared();
    mag = sqrt(magsquared);
    if(mag < ship.radius + goal.radius) {
        // Level Complete
        pthread_mutex_lock(&state.modeMutex);
        state.mode = MODE_LEVEL_WON;
        pthread_mutex_unlock(&state.modeMutex);

        pthread_mutex_lock(&state.miscMutex);
        if(state.level == state.levelsInSector && state.sector == state.highestSector) {
            if(state.sector == state.sectorsInGalaxy) {

            } else if(state.sector == state.highestSector) {
                state.highestSector++;
                state.highestLevel = 1;
            }
        } else if(state.level == state.highestLevel && state.sector == state.highestSector) {
            state.highestLevel++;
        }
        pthread_mutex_unlock(&state.miscMutex);

        // Save Game
        state.importer.saveGame();
        return;
    }

    // Move the ship
    ship.velocity += ship.acceleration * timeDelta;
    ship.position += ship.velocity * timeDelta;
    ship.acceleration = 0.0f;
}
