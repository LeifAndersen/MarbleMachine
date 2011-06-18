#ifndef PHYSICS_H
#define PHYSICS_H

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
    GameState & state;
};

#endif // PHYSICS_H
