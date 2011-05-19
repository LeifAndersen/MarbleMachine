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
    enum plankSide {
        topSide,
        rightSide,
        bottomSide,
        leftSide
    };

    GameState & state;

    bool circleSquareCollide(float cirR, Point cirPos, float rectW, float rectH, Point rectPos);
    Point reflect(Point incidence, Point surfaceNormal);

    static float terminalVelocity;
};

#endif // PHYSICS_H
