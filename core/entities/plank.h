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
    virtual void draw();
    float length;
    float width;
private:
    static std::vector<Point> verts;
    GLuint buffer;
};

#endif // PLANK_H
