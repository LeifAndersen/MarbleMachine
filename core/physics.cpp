#include <list>

#include "physics.h"
#include "game_state.h"
#include "math.h"
#include "stdlib.h"

using namespace std;

Physics::Physics(GameState & state) : state(state)
{
}

void Physics::update(float timeDelta)
{
    // First, move the marble
    if(state.marble.velocity.magnitude() <= terminalVelocity) {
        state.marble.acceleration.y -= 9.8*timeDelta;
        state.marble.velocity += state.marble.acceleration*timeDelta;
    }
    state.marble.position += state.marble.velocity*timeDelta;

    // Then, check for collisions
    // First, broad check to see what's in the veciinity
    list<Plank *> planks = state.grid.getPlanks(state.marble.position.x,
                                                state.marble.position.y);
    list<Cannon *> cannons = state.grid.getCannons(state.marble.position.x,
                                                   state.marble.position.y);
    // Second, more precice check for close objects
    for(list<Plank *>::iterator i = planks.begin();
        i != planks.end(); i++) {
        // TODO
    }
    for(list<Cannon *>::iterator i = cannons.begin();
        i != cannons.end(); i++) {
        // TODO
    }

    // If it's reached the goal, you win
}

// This can probably just be set by hand, as we're only
// Droping one object at the moment.  And this is quicker...
float Physics::terminalVelocity = 50;
