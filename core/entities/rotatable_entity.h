#ifndef ROTATABLE_ENTITY_H
#define ROTATABLE_ENTITY_H

#include "entity.h"

class RotatableEntity : public Entity
{
public:
    RotatableEntity();
    static void loadData();
    virtual void draw();
    float rotation;
    Point normal; // TODO -- make sure the normal is always the side that is facing rotation + 90º
                  // based on the assumption that a plank lying flat has a rotation of 0º
private:
    enum State { PLACE, MOVE, ROTATE };
    State state;
};

#endif // ROTATABLE_ENTITY_H
