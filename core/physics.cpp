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

    // First run the equations on every planet/asteroid
    for(SphereIterator i = state.planets.begin(); i != planetEnd; i++) {
        // Planet - Planet
        for(SphereIterator j = state.planets.begin(); j != planetEnd; j++) {

        }

        // Planet - AntiPlanet
        for(SphereIterator j = state.antiPlanets.begin(); j != antiPlanetEnd; j++) {

        }

        // Planet - Ship
    }

    // Next run through it for anti-planets
    for(SphereIterator i = state.antiPlanets.begin(); i != antiPlanetEnd; i++) {
        // AntiPlanet - Planet
        for(SphereIterator j = state.planets.begin(); j != planetEnd; j++) {

        }

        // AntiPlanet - AntiPlanet
        for(SphereIterator j = state.antiPlanets.begin(); j != antiPlanetEnd; j++) {

        }

        // AntiPlanet - Ship
    }

    // Next on the ship
    // Ship - Planet
    for(SphereIterator j = state.planets.begin(); j != planetEnd; j++) {

    }

    // Ship - AntiPlanet
    for(SphereIterator j = state.antiPlanets.begin(); j != antiPlanetEnd; j++) {

    }
}
