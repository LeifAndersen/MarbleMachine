#ifndef CANNON_H
#define CANNON_H

#include "entity.h"

class Cannon : public Entity
{
public:
    Cannon();
    virtual void draw();

    float rotation;
};

#endif // CANNON_H
