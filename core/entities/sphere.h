#ifndef SPHERE_H
#define SPHERE_H

#include "entity.h"

class Sphere : public Entity
{
public:
    Sphere();

    static void loadData();
    virtual void draw();
    float radius;
};

#endif // SPHERE_H
