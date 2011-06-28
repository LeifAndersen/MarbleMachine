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

    Point position;
    Point velocity;
    Point acceleration;

    Point rotation;

    float mass;
    bool isMovable;
};

#endif // ENTITY_H
