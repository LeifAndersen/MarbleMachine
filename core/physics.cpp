#include <list>
#include <cstdlib>
#include <cmath>

#include "physics.h"
#include "game_state.h"
#include "os_calls.h"

using namespace std;

#define GRAVITY -1
#define TERMINAL_VELOCITY -10

Physics::Physics(GameState & state) : state(state)
{
}

void Physics::update(float timeDelta)
{
    // Get local references for speed
    SphereIterator planetEnd = state.planets.end();
    SphereIterator antiPlanetEnd = state.antiPlanets.end();
    Sphere & ship = state.ship;
    Point distance;
    float pull;

    // Make sure to use whatever parts of the equation possible twice
    // (namely effecting both planets).

    // First run the equations on every planet/asteroid
    for(SphereIterator i = state.planets.begin(); i != planetEnd; i++) {
        // Planet - Planet
        for(SphereIterator j = state.planets.begin(); j != planetEnd; j++) {
            if(i == j)
                continue;

            // First move the planets
            distance = i->position - j->position;
            pull = M_G/distance.magnitudeSquared();
            distance.normalize();
            i->acceleration -= distance*pull*j->mass;
            j->acceleration -= distance*pull*i->mass;

            // Next do colisions:
        }

        // Planet - AntiPlanet
        for(SphereIterator j = state.antiPlanets.begin(); j != antiPlanetEnd; j++) {
            // First move the planets
            distance = i->position - j->position;
            pull = M_G/distance.magnitudeSquared();
            distance.normalize();
            i->acceleration += distance*pull*j->mass;
            j->acceleration -= distance*pull*i->mass;

            // Next do colisions:
        }

        // Planet - Ship
        // First move the planets
        distance = i->position - ship.position;
        pull = M_G/distance.magnitudeSquared();
        distance.normalize();
        i->acceleration -= distance*pull*ship.mass;
        ship.acceleration -= distance*pull*i->mass;

        // Next do colisions:
    }

    // Next run through it for anti-planets
    for(SphereIterator i = state.antiPlanets.begin(); i != antiPlanetEnd; i++) {
        // AntiPlanet - AntiPlanet
        for(SphereIterator j = state.antiPlanets.begin(); j != antiPlanetEnd; j++) {
            if(i == j)
                continue;

            // First move the planets
            distance = i->position - j->position;
            pull = M_G/distance.magnitudeSquared();
            distance.normalize();
            i->acceleration += distance*pull*j->mass;
            j->acceleration += distance*pull*i->mass;

            // Next do colisions:
        }

        // AntiPlanet - Ship
        // First move the planets
        distance = i->position - ship.position;
        pull = M_G/distance.magnitudeSquared();
        distance.normalize();
        i->acceleration -= distance*pull*ship.mass;
        ship.acceleration += distance*pull*i->mass;

        // Next do colisions:
    }
}
