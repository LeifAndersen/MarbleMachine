#include "include_opengl.h"
#include "entity.h"


Entity::Entity() : position(Point()), velocity(Point()), acceleration(Point()),
    rotation(0.0f, 0.0f, 0.0f), mass(0), isMovable(false)
{

}

Entity::Entity(bool isMovable) : position(Point()), velocity(Point()),
    acceleration(Point()), rotation(0.0f, 0.0f, 0.0f), mass(0), isMovable(isMovable)
{

}

Entity::Entity(Point position, bool isMovable) : position(position), velocity(Point()),
    acceleration(Point()), rotation(0.0f, 0.0f, 0.0f), mass(0), isMovable(isMovable)
{

}

Entity::Entity(Point position) : position(position), velocity(Point()),
    acceleration(Point()), rotation(0.0f, 0.0f, 0.0f), mass(0), isMovable(false)
{
}

Entity::Entity(Point position, Point velocity) : position(position),
    velocity(velocity), acceleration(acceleration), rotation(0.0f, 0.0f, 0.0f),
    mass(0), isMovable(false)
{
}

Entity::Entity(Point position, Point velocity, Point acceleration) :
    position(position), velocity(velocity), acceleration(acceleration),
    rotation(0.0f, 0.0f, 0.0f), mass(0), isMovable(false)
{
}

void Entity::loadData()
{

}

void Entity::draw()
{

}
