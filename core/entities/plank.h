#ifndef PLANK_H
#define PLANK_H

#include "entity.h"

class Plank : public Entity
{
public:
    Plank();
    virtual void draw();

    // First person to use this, pick radians or degrees please
    float rotation;
};

#endif // PLANK_H
