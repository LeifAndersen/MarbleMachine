#ifndef PHYSICS_H
#define PHYSICS_H

#include "entity.h"
#include "sphere.h"

class GameState;


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

    /**
      * Called when two planets collide with each other.
      *
      * Input: Planets:   The list of planets that was colided upon
      *        i:         The first planet in the collision
      *        j:         The second planet in the colision
      *        chunkSize: The size of chunks that are created from the explosion.
      *                       Note that larger chunks make fewer chunks
      *
      */
    void planetPlanetCollision(std::vector<Sphere> & planets, Sphere * i,
                               Sphere * j, float chunkSize);
    GameState & state;
};

#endif // PHYSICS_H
