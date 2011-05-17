#include "include_opengl.h"
#include "entity.h"


Entity::Entity() : position(Point()), velocity(Point()), acceleration(Point()),
    isMovable(false)
{

}

Entity::Entity(bool isMovable) : position(Point()), velocity(Point()),
    acceleration(Point()), isMovable(isMovable)
{

}

Entity::Entity(Point position, bool isMovable) : position(position), velocity(Point()),
    acceleration(Point()), isMovable(isMovable)
{

}

Entity::Entity(Point position) : position(position), velocity(Point()),
    acceleration(Point()), isMovable(false)
{
}

Entity::Entity(Point position, Point velocity) : position(position),
    velocity(velocity), acceleration(acceleration), isMovable(false)
{
}

Entity::Entity(Point position, Point velocity, Point acceleration) :
    position(position), velocity(velocity), acceleration(acceleration),
    isMovable(false)
{
}

void Entity::loadData()
{

}

void Entity::draw()
{

}
