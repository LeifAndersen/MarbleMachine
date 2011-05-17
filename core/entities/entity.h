#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include "point.h"
#include "drawable.h"

class Entity : Drawable
{
public:
    Entity();
    Entity(bool isMovable);
    Entity(Point position);
    Entity(Point position, bool isMovable);
    Entity(Point position, Point velocity);
    Entity(Point position, Point velocity, Point acceleration);
    static void loadData();
    virtual void draw();

    Point position;
    Point velocity;
    Point acceleration;
    float mass;
    bool isMovable;
private:
    static std::vector<int> verts;
    static std::vector<int> triangle_faces;
    enum State { MOVE, PLACE };
    State state;
};

#endif // ENTITY_H
