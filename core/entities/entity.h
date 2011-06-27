#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>
#include "point.h"
#include "drawable.h"

class Entity : public Drawable
{
public:
    Entity(Point position = Point(0.0f, 0.0f, 0.0f),
           Point velocity = Point(0.0f, 0.0f, 0.0f),
           Point acceleration = Point(0.0f, 0.0f, 0.0f),
           bool isMovable = false);
    static void loadData();
    virtual void draw();

    Point position;
    Point velocity;
    Point acceleration;

    Point rotation;
    Point normal; // TODO -- make sure the normal is always the side that is facing rotation + 90º
                  // based on the assumption that a plank lying flat has a rotation of 0º

    float mass;
    bool isMovable;
};

#endif // ENTITY_H
