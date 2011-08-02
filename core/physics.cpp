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
    SphereIterator endPlanets = state.planets.end();
    Sphere * planet;
    Point distance;
    float mag;
    float magsquared;
    float pull;
    int randNum;

    // Make sure to use whatever parts of the equation possible twice
    // (namely effecting both planets).

    // Run the acceleration equations on every planet/asteroid
    for(SphereIterator i = state.planets.begin(); i != endPlanets; i++) {
        // Planet - Planet
        for(SphereIterator j = i; j != endPlanets; j++) {
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
                randNum = rand() % (int)floorf(j->mass/2);
                for(int k = 0; k < randNum; k++) {
                    state.planets.push_back(Sphere());
                    planet = &state.planets.back();
                    planet->acceleration = 0.0f;
                    planet->velocity = (j->velocity*-1) +
                            Point(((rand() % RAND_VAR_CHANGE) - HALF_RAND_VAR_CHANGE)/10.0f,
                                   ((rand() % RAND_VAR_CHANGE) - HALF_RAND_VAR_CHANGE)/10.0f,
                                   0);
                    planet->position = (j->position) +
                            Point(((rand() % RAND_VAR_CHANGE))/10.0f,
                                  ((rand() % RAND_VAR_CHANGE))/10.0f,
                                  0);
                    planet->mass = i->mass/randNum/2;
                    planet->radius = i->radius/randNum/2;
                }

                randNum = rand() % (int)floorf(i->mass/2);
                for(int k = 0; k < randNum; k++) {
                    state.planets.push_back(Sphere());
                    planet = &state.planets.back();
                    planet->acceleration = 0.0f;
                    planet->velocity = (j->velocity*-1) +
                            Point(((rand() % RAND_VAR_CHANGE) - HALF_RAND_VAR_CHANGE)/10.0f,
                                   ((rand() % RAND_VAR_CHANGE) - HALF_RAND_VAR_CHANGE)/10.0f,
                                   0);
                    planet->position = (j->position) +
                            Point(((rand() % RAND_VAR_CHANGE))/10.0f,
                                  ((rand() % RAND_VAR_CHANGE))/10.0f,
                                  0);
                    planet->mass = j->mass/randNum/2;
                    planet->radius = j->radius/randNum/2;
                }

                // Delete the old planets
                state.planets.erase(j);
                j = endPlanets = state.planets.end();
                state.planets.erase(i--);

                pthread_mutex_unlock(&state.planetsMutex);
            }
        }

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
            // TODO
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
        return;
    }

    // Move the ship
    ship.velocity += ship.acceleration * timeDelta;
    ship.position += ship.velocity * timeDelta;
    ship.acceleration = 0.0f;
}
