#ifndef PHYSICS_H
#define PHYSICS_H

class GameState;

#include "plank.h"
#include "cannon.h"

class Physics
{
public:
    Physics(GameState & state);

    /**
      * Causes the gamestate to move to the next state.
      * This is where the physics magic happens.
      */
    void update(float timeDelta);
private:
    GameState & state;

    void plankCollide(Plank & plank);
    void cannonCollide(Cannon & cannon);

    static float terminalVelocity;
};

#endif // PHYSICS_H
