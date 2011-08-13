#include <list>
#include <cstdlib>
#include <cmath>

#include "physics.h"
#include "game_state.h"
#include "os_calls.h"

#define M_G 1.0f //6.67428E-11
#define SHIP_G 100.0f
#define RAND_VAR_CHANGE 4
#define HALF_RAND_VAR_CHANGE 2

using namespace std;

Physics::Physics(GameState & state) : state(state)
{
}

void Physics::update(float timeDelta)
{
    // Get local references for speed
    Sphere & ship = state.ship;
    Sphere & goal = state.goal;
    Point distance;
    float mag;
    float magsquared;
    float pull;

    // Make sure to use whatever parts of the equation possible twice
    // (namely effecting both planets).

    // Run the acceleration equations on every planet/asteroid
    for(unsigned int iter = 0; iter != state.planets.size(); iter++) {

        Sphere * i = &state.planets[iter];

        bool collision = false;

        // Planet - Planet
        for(unsigned int jiter = iter+1; jiter != state.planets.size(); jiter++) {

            Sphere * j = &state.planets[jiter];

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

                planetPlanetCollision(state.planets, i, j, 1);
                i = &state.planets[iter];
                j = &state.planets[jiter];
                planetPlanetCollision(state.planets, i, j, 1);

                // Delete the old planets
                state.planets.erase(state.planets.begin()+jiter);
                state.planets.erase(state.planets.begin()+(iter--));
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

void Physics::planetPlanetCollision(std::vector<Sphere> &planets, Sphere *i,
                                    Sphere *j, float chunkSize)
{
    unsigned int randNum;
    Sphere * planet;

    // Add in some new, smaller, planets
    // temporarily just 4, make it a bit more random later.
    randNum = rand() % ((unsigned int)(fabsf(i->mass/chunkSize))+1);
    for(unsigned int k = 0; k < randNum; k++) {
        planets.push_back(Sphere());
        planet = &state.planets.back();
        planet->acceleration = 0.0f;
        planet->velocity = (i->velocity/2.0f+j->velocity) +
                Point(((rand() % RAND_VAR_CHANGE) - HALF_RAND_VAR_CHANGE),
                       ((rand() % RAND_VAR_CHANGE) - HALF_RAND_VAR_CHANGE),
                       0);
        planet->position = (i->position-j->position.normal_vector()*j->radius) +
                Point(((rand() % RAND_VAR_CHANGE)),
                      ((rand() % RAND_VAR_CHANGE)),
                      0);
        planet->mass = i->mass/randNum * chunkSize;
        planet->radius = i->radius/randNum * chunkSize;
        if(planet->radius < MINIMUM_RADIUS || fabsf(planet->mass) < MINIMUM_WEIGHT)
            planets.erase(planets.end());
    }

    randNum = rand() % ((unsigned int)(fabsf(j->mass/chunkSize))+1);
    for(unsigned int k = 0; k < randNum; k++) {
        planets.push_back(Sphere());
        planet = &state.planets.back();
        planet->acceleration = 0.0f;
        planet->velocity = (i->velocity+j->velocity/2.0f) +
                Point(((rand() % RAND_VAR_CHANGE) - HALF_RAND_VAR_CHANGE),
                       ((rand() % RAND_VAR_CHANGE) - HALF_RAND_VAR_CHANGE),
                       0);
        planet->position = (j->position-i->position.normal_vector()*j->radius) +
                Point(((rand() % RAND_VAR_CHANGE)),
                      ((rand() % RAND_VAR_CHANGE)),
                      0);
        planet->mass = j->mass/randNum * chunkSize;
        planet->radius = j->radius/randNum * chunkSize;
        if(planet->radius < MINIMUM_RADIUS || fabsf(planet->mass) < MINIMUM_WEIGHT)
            planets.erase(planets.end());
    }
}
