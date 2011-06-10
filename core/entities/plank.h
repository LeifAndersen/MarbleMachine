#ifndef PLANK_H
#define PLANK_H

#include <vector>
#include "include_opengl.h"

#include "entity.h"
#include "point.h"

class Plank : public Entity
{
public:
    Plank();
    static void loadData();
    float length;
    float width;
	float height;
    virtual void loadMVMatrix();

    // Hack to make a virtual static variable
    virtual std::vector<DrawablePoint> & getVerts();
    virtual std::vector<GLushort> & getIndices();

    static std::vector<DrawablePoint> verts;
    static std::vector<GLushort> indices;
};

#endif // PLANK_H
