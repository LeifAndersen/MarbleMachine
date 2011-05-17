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
    for(PlankIterator i = state.levelPlanks.begin();
        i != state.levelPlanks.end(); i++) {
        plankCollide(*i);
    }
    for(PlankIterator i = state.playerPlanks.begin();
        i != state.playerPlanks.end(); i++) {
        plankCollide(*i);
    }
    for(CannonIterator i = state.levelCannons.begin();
        i != state.playerCannons.end(); i++) {
        cannonCollide(*i);
    }
    for(CannonIterator i = state.playerCannons.begin();
        i != state.playerCannons.end(); i++) {
        cannonCollide(*i);
    }

    // If it's reached the goal, you win
}

void Physics::plankCollide(Plank &plank)
{
    Point distance;
    distance.x = abs(state.marble.position.x
                     - plank.position.x - plank.length/2);
    distance.y = abs(state.marble.position.y
                     - plank.position.y - plank.width/2);


}

void Physics::cannonCollide(Cannon &cannon)
{

}

// This can probably just be set by hand, as we're only
// Droping one object at the moment.  And this is quicker...
float Physics::terminalVelocity = 50;
