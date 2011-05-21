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
    virtual void draw(GLuint vertex_attrib);
    float radius;
private:
    static std::vector<GLfloat> body;
    static int body_size;
    static GLuint buffers[1];
};

#endif // SPHERE_H
