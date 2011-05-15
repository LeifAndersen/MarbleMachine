#ifndef PLANK_H
#define PLANK_H

#include "entity.h"
#include "rotatable_entity.h"

class Plank : public RotatableEntity
{
public:
    Plank();
    virtual void draw();
};

#endif // PLANK_H
