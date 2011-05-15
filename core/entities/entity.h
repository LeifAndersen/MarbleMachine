#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include "point.h"

class Entity
{
public:
    Entity();
    Entity(Point position);
    Entity(Point position, Point velocity);
    Entity(Point position, Point velocity, Point acceleration);
    virtual void draw();

    Point position;
    Point velocity;
    Point acceleration;
private:
    std::vector<int> verts;
    std::vector<int> triangle_faces;
};

#endif // ENTITY_H