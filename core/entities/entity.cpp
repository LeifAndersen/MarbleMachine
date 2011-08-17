#include "include_opengl.h"
#include "entity.h"


Entity::Entity(Point position,
               Point velocity,
               Point acceleration,
               bool isMovable) :
    position(position),
    velocity(velocity),
    acceleration(acceleration),
    rotation(0.0f, 0.0f, 0.0f),
    angularVelocity(0.0f, 0.0f, 0.0f),
    angularAcceleration(0.0f, 0.0f, 0.0f),
    mass(0),
    isMovable(isMovable)
{
}

Entity::~Entity()
{

}

Entity::Entity(const Entity &other) :
    Drawable(other),
    position(other.position),
    velocity(other.velocity),
    acceleration(other.acceleration),
    rotation(other.rotation),
    angularVelocity(other.angularVelocity),
    angularAcceleration(other.angularAcceleration),
    mass(other.mass),
    isMovable(other.isMovable)
{
}

Entity & Entity::operator =(const Entity & other)
{
    Drawable * super = this;
    (*super) = other;
    position = other.position;
    velocity = other.velocity;
    acceleration = other.acceleration;
    rotation = other.rotation;
    angularVelocity = other.angularVelocity;
    angularAcceleration = other.angularAcceleration;
    mass = other.mass;
    isMovable = other.isMovable;
    return *this;
}
