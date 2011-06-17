#ifndef CANNON_H
#define CANNON_H

#include <string>
#include "include_opengl.h"

#include "entity.h"

class Cannon : public Entity
{
public:
    Cannon();
    static void loadData();
    virtual void draw();
    float width;
    float length;
	float height;

private:
    static std::vector<Point> verts;
    static GLuint buffer;
};

#endif // CANNON_H
