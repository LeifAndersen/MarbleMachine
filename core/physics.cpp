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
    // First, move the marble
    timeDelta = timeDelta / 10; // SLOWER so we can debug.

}
