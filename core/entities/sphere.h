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

    float radius;

    virtual void loadMVMatrix();

    // Hack to make a virtual static variable
    virtual std::vector<DrawablePoint> & getVerts();
    virtual std::vector<GLushort> & getIndices();

    static std::vector<DrawablePoint> verts;
    static std::vector<GLushort> indices;
};

#endif // SPHERE_H
