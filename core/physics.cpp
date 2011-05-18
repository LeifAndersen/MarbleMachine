#include "physics.h"
#include "game_state.h"
#include "math.h"
#include "stdlib.h"

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
    for(PlankIterator i = state.planks.begin();
        i != state.planks.end(); i++) {
        // TODO
    }
    for(CannonIterator i = state.cannons.begin();
        i != state.cannons.end(); i++) {
        // TODO
    }

    // If it's reached the goal, you win
}

// This can probably just be set by hand, as we're only
// Droping one object at the moment.  And this is quicker...
float Physics::terminalVelocity = 50;
