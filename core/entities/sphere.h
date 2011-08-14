#ifndef SPHERE_H
#define SPHERE_H

#include "include_opengl.h"

#include "entity.h"
#include "point.h"
#include "matrix.h"

class Sphere : public Entity
{
public:
    Sphere();
    ~Sphere();
    Sphere(const Sphere & other);
    Sphere & operator =(const Sphere & other);

    float radius;

    virtual void loadMVMatrix();

};

#endif // SPHERE_H
