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

    ~Entity();

    Entity(const Entity & other);

    Entity & operator =(const Entity & other);

    Point position;
    Point velocity;
    Point acceleration;

    Point rotation;
    Point angularVelocity;
    Point angularAcceleration;

    float mass;
    bool isMovable;
};

#endif // ENTITY_H
