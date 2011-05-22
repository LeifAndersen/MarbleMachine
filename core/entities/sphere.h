#ifndef SPHERE_H
#define SPHERE_H

#include "include_opengl.h"

#include "entity.h"
#include "point.h"

class Sphere : public Entity
{
public:
    Sphere();

    static void loadData(GLuint gvPositionHandle);
    virtual void draw();
    float radius;
private:
    static std::vector<DrawablePoint> verts;
    static std::vector<GLushort> indices;

    // Buffer 0 for DrawablePoints
    // Buffer 1 for indices
    static GLuint buffers[2];
    static GLuint gvPositionHandle;
};

#endif // SPHERE_H
