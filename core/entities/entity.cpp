#include "include_opengl.h"
#include "entity.h"


Entity::Entity(Point position,
               Point velocity,
               Point acceleration,
               bool isMovable) : position(position),
    velocity(velocity), acceleration(acceleration),
    rotation(0.0f, 0.0f, 0.0f),
    mass(0), isMovable(isMovable)
{
}

void Entity::loadData()
{

}

void Entity::draw()
{

}
