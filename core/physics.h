#ifndef PHYSICS_H
#define PHYSICS_H

#include "entity.h"

class GameState;

#define M_G 6.67428E-11

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

    /**
      * Update the position of the entity given, with respect to the
      * time delta given.
      */
    void updatePosition(Entity & entity, float timeDelta);
};

#endif // PHYSICS_H
