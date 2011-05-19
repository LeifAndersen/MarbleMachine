#ifndef CANNON_H
#define CANNON_H

#include <string>
#include "include_opengl.h"

#include "entity.h"
#include "rotatable_entity.h"

class Cannon : public RotatableEntity
{
public:
    Cannon();
    static void loadData();
    virtual void draw();
    float width;
    float length;

private:
    static std::vector<Point> verts;
    static GLuint buffer;
};

#endif // CANNON_H
