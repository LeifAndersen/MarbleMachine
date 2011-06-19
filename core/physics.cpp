#include <list>
#include <cstdlib>
#include <cmath>

#include "physics.h"
#include "game_state.h"
#include "os_calls.h"

#define M_G 6.67428E-11
#define RAND_VAR_CHANGE 10
#define HALF_RAND_VAR_CHANGE 5

using namespace std;

Physics::Physics(GameState & state) : state(state)
{
    srand(MMtime());
}

void Physics::update(float timeDelta)
{
    // Get local references for speed
    SphereIterator planetEnd = state.planets.end();
    Sphere & ship = state.ship;
    Sphere & planet = state.planets.front();
    Point distance;
    float mag;
    float magsquared;
    float pull;
    int randNum;

    // Make sure to use whatever parts of the equation possible twice
    // (namely effecting both planets).

    // First, move each object based on it's acceleration:
    for(SphereIterator i = state.planets.begin(); i != planetEnd; i++) {
        i->velocity += i->acceleration * timeDelta;
        i->position += i->velocity * timeDelta;
    }
    ship.velocity += ship.acceleration * timeDelta;
    ship.position += ship.velocity * timeDelta;

    // Run the acceleration equations on every planet/asteroid
    for(SphereIterator i = state.planets.begin(); i != planetEnd; i++) {
        // Planet - Planet
        for(SphereIterator j = i; j != planetEnd; j++) {
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

                // Add in some new, smaller, planets
                // temporarily just 4, make it a bit more random later.
                randNum = rand() % 5;
                for(int k = 0; k < randNum; k++) {
                    state.planets.push_back(Sphere());
                    planet = state.planets.back();
                    planet.acceleration = (i->acceleration*-1) +
                            Point((rand() % RAND_VAR_CHANGE) - HALF_RAND_VAR_CHANGE,
                                   (rand() % RAND_VAR_CHANGE) - HALF_RAND_VAR_CHANGE,
                                   (rand() % RAND_VAR_CHANGE) - HALF_RAND_VAR_CHANGE);
                    planet.velocity = (i->velocity*-1) +
                            Point((rand() % RAND_VAR_CHANGE) - HALF_RAND_VAR_CHANGE,
                                   (rand() % RAND_VAR_CHANGE) - HALF_RAND_VAR_CHANGE,
                                   (rand() % RAND_VAR_CHANGE) - HALF_RAND_VAR_CHANGE);
                    planet.position = (i->position) +
                            Point((rand() % RAND_VAR_CHANGE),
                                  (rand() % RAND_VAR_CHANGE),
                                  (rand() % RAND_VAR_CHANGE));
                }

                randNum = rand() % 5;
                for(int k = 0; k < randNum; k++) {
                    state.planets.push_back(Sphere());
                    planet = state.planets.back();
                    planet.acceleration = (j->acceleration*-1) +
                            Point((rand() % RAND_VAR_CHANGE) - HALF_RAND_VAR_CHANGE,
                                   (rand() % RAND_VAR_CHANGE) - HALF_RAND_VAR_CHANGE,
                                   (rand() % RAND_VAR_CHANGE) - HALF_RAND_VAR_CHANGE);
                    planet.velocity = (j->velocity*-1) +
                            Point((rand() % RAND_VAR_CHANGE) - HALF_RAND_VAR_CHANGE,
                                   (rand() % RAND_VAR_CHANGE) - HALF_RAND_VAR_CHANGE,
                                   (rand() % RAND_VAR_CHANGE) - HALF_RAND_VAR_CHANGE);
                    planet.position = (j->position) +
                            Point((rand() % RAND_VAR_CHANGE),
                                  (rand() % RAND_VAR_CHANGE),
                                  (rand() % RAND_VAR_CHANGE));
                }

                // Delete the old planets
                j = state.planets.erase(j);
                j--;
                i = state.planets.erase(i);
                i--;
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
        ship.acceleration += distance*pull*i->mass;

        // Next do colisions:
        if(mag < i->radius + ship.radius) {
            i = state.planets.erase(i);
            i--;
        }
    }
}
