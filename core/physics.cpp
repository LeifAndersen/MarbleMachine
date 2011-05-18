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

bool Physics::circleSquareCollide(float cirR, Point cirPos, float rectW, float rectH, Point rectPos) {
    float cirDistX = abs(cirPos.x - rectPos.x - rectW/2);
    float cirDistY = abs(cirPos.y - rectPos.y - rectH/2);

    if (cirDistX > (rectW/2 + cirR)) { return false; }
    if (cirDistY > (rectH/2 + cirR)) { return false; }

    if (cirDistX <= (rectW/2)) { return true; }
    if (cirDistY <= (rectH/2)) { return true; }

    float cornerDistance_sq = pow((cirDistX - rectW/2), 2) +
                         pow((cirDistY - rectH/2), 2);

    return (cornerDistance_sq <= pow(cirR, 2));
}

// This can probably just be set by hand, as we're only
// droping one object at the moment.  And this is quicker...
float Physics::terminalVelocity = 50;
