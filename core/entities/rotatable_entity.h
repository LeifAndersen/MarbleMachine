#ifndef ROTATABLE_ENTITY_H
#define ROTATABLE_ENTITY_H

#include "entity.h"

class RotatableEntity : public Entity
{
public:
    RotatableEntity();
    virtual void draw();
    float rotation;
};

#endif // ROTATABLE_ENTITY_H
