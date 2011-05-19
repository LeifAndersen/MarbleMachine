#ifndef CANNON_H
#define CANNON_H

#include "entity.h"
#include "rotatable_entity.h"

class Cannon : public RotatableEntity
{
public:
    Cannon();
    static void loadData();
    virtual void draw();
    float width;
    float length;
};

#endif // CANNON_H
