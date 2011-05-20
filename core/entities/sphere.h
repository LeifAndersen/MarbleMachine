#ifndef SPHERE_H
#define SPHERE_H

#include "include_opengl.h"

#include "entity.h"
#include "point.h"

class Sphere : public Entity
{
public:
    Sphere();

    static void loadData();
    virtual void draw();
    float radius;
private:
    static std::vector<float> body;
    static GLuint buffers[1];
};

#endif // SPHERE_H
