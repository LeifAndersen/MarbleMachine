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
};

#endif // CANNON_H
