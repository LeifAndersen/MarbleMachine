#ifndef PLANK_H
#define PLANK_H

#include "entity.h"
#include "rotatable_entity.h"

class Plank : public RotatableEntity
{
public:
    Plank();
    static void loadData();
    virtual void draw();
    float length;
    float width;
};

#endif // PLANK_H
