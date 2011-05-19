#ifndef GOAL_H
#define GOAL_H

#include <vector>
#include "include_opengl.h"

#include "entity.h"
#include "point.h"

class Goal : public Entity
{
public:
    Goal();
    static void loadData();
    virtual void draw();
private:
    static std::vector<Point> verts;
    static GLuint buffer;
};

#endif // GOAL_H
