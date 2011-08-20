#include <list>
#include <cstdlib>
#include <cmath>
#include "physics.h"
#include "game_state.h"
#include "os_calls.h"

#define M_G 6.0f //6.67428E-11
#define SHIP_G 60.0f
#define PARTICLE_COUNT 125
#define PARTICLE_COUNT_VARIENT 50
#define PARTICLE_LIFE_TIME 30
#define PARTICLE_LIFE_TIME_VARIANT 20
#define PARTICLE_VELOCITY 1
#define PARTICLE_VELOCITY_VARIENT 3
#define PARTICLE_TRANSFER_VELOCITY 100.0f
#define PARTICLE_RADIUS_DIVISOR 5
#define PARTICLE_RADIUS_DIVISOR_VARIENT 3
#define PARTICLE_RADIUS_REMOVAL_DIVSOR 100.0f
#define PLANET_COLLISION_DIVISOR 3 // mass and radious devided by this, rest becomes particles
#define PLANET_COLLISION_DIVISOR_VARIENT 1

using namespace std;

Physics::Physics(GameState & state) : state(state)
{
}

void Physics::update(float timeDelta)
{
    // Get local references for speed
    Sphere & ship = state.ship;
    Sphere & goal = state.goal;
    Sphere planet;
    Point distance;
    float mag;
    float magsquared;
    float pull;
    float collisionMass;
    float totalMass;
    float particles;
    float particleDevisor;
    float radiusRemaining;

    // Make sure to use whatever parts of the equation possible twice
    // (namely effecting both planets).

    // Run the acceleration equations on every planet/asteroid
    pthread_mutex_lock(&state.planetsAddMutex);
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
            i->acceleration -= distance*(pull*j->mass);
            j->acceleration += distance*(pull*i->mass);

            // Next do colisions:
            if(mag < i->radius + j->radius) {

                pthread_mutex_lock(&state.planetsMutex);

                // Play the sound if efx are on.
                if(!state.efxMuted) {
                    playSound(state.explosion);
                }

                // A collision has occured
                // First make a few planets capable of destroying new planets.
                totalMass = i->mass + j->mass;
                radiusRemaining = i->radius+j->radius;
                collisionMass = totalMass
                        / (PLANET_COLLISION_DIVISOR - rand()
                           % PLANET_COLLISION_DIVISOR_VARIENT);

                planet.mass = collisionMass;
                planet.velocity = i->velocity+j->velocity;
                planet.position = i->position+(j->position-i->position)/2.0f;
                planet.radius = radiusRemaining
                        / (PLANET_COLLISION_DIVISOR - rand()
                           % PLANET_COLLISION_DIVISOR_VARIENT);
                radiusRemaining -= planet.radius;
                planet.acceleration = 0.0f;
                state.planets[iter] = planet;

                // Then, make lots of particles, for visual effects.
                particles = PARTICLE_COUNT - random() % PARTICLE_COUNT_VARIENT;
                for(unsigned int kiter = 0; kiter < particles; kiter++) {

                    // Remember that how long a particle has to live is stored in acceleration.x
                    planet.acceleration.x = PARTICLE_LIFE_TIME
                            - rand() % PARTICLE_LIFE_TIME_VARIANT;

                    particleDevisor = ((rand() % 5) + 1)/2.0f;
                    planet.position = i->position+(j->position-i->position)
                            / particleDevisor;
                    planet.velocity.x = PARTICLE_VELOCITY - rand() % PARTICLE_VELOCITY_VARIENT;
                    planet.velocity.y = PARTICLE_VELOCITY - rand() % PARTICLE_VELOCITY_VARIENT;
                    planet.velocity.z = PARTICLE_VELOCITY - rand() % PARTICLE_VELOCITY_VARIENT;
                    planet.velocity.normalize();
                    planet.velocity *= PARTICLE_VELOCITY - rand() % PARTICLE_VELOCITY_VARIENT;
                    planet.velocity += (i->velocity*i->mass+j->velocity*j->mass)
                            /PARTICLE_TRANSFER_VELOCITY;
                    planet.radius = radiusRemaining
                            / (PARTICLE_RADIUS_DIVISOR - rand()
                               % PARTICLE_RADIUS_DIVISOR_VARIENT);
                    radiusRemaining -= planet.radius/PARTICLE_RADIUS_REMOVAL_DIVSOR;
                    state.particles.push_back(planet);
                }

                // Delete the old planets
                state.planets.erase(state.planets.begin()+jiter);
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
        i->acceleration -= distance*(pull*ship.mass);
        ship.acceleration += distance*(pull*i->mass*SHIP_G);

        // Next do colisions:
        if(mag < i->radius + ship.radius) {
            pthread_mutex_lock(&state.modeMutex);
            pthread_mutex_unlock(&state.planetsAddMutex);
            state.mode = MODE_LEVEL_LOST;
            pthread_mutex_unlock(&state.modeMutex);
            return;
        }

        // Finally move the asteroid
        i->velocity += i->acceleration * timeDelta;
        i->position += i->velocity * timeDelta;
        i->angularVelocity += i->angularAcceleration * timeDelta;
        i->rotation += i->angularVelocity * timeDelta;

        // And reset the acceleration for the next go arround
        i->acceleration = 0.0f;
        i->angularAcceleration = 0.0f;
    }

    // Move the particles
    // Life time particle has left to stay alive is in accelerationl.x
    for(unsigned int iter = 0; iter < state.particles.size(); iter++) {
        Sphere * i = &state.particles[iter];
        i->position += i->velocity * timeDelta;
        i->rotation += i->angularVelocity * timeDelta;
        i->acceleration.x -= timeDelta;
        if(i->acceleration.x <= 0) {
            pthread_mutex_lock(&state.planetsMutex);
            *i = state.particles[state.particles.size() - 1];
            state.particles.erase(state.particles.end());
            iter--;
            pthread_mutex_unlock(&state.planetsMutex);
        }
    }
    pthread_mutex_unlock(&state.planetsAddMutex);

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
    ship.angularVelocity += ship.acceleration * timeDelta;
    ship.rotation += ship.angularVelocity * timeDelta;
    ship.angularAcceleration = 0.0f;

    // Rotate the active planet a bit:
    state.activePlanet.rotation += state.activePlanet.angularVelocity * timeDelta;
}
