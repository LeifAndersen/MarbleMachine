#include "include_opengl.h"
#include "entity.h"


Entity::Entity() : position(Point()), velocity(Point()), acceleration(Point())
{

}

Entity::Entity(Point position) : position(position), velocity(Point()),
    acceleration(Point())
{
}

Entity::Entity(Point position, Point velocity) : position(position),
    velocity(velocity), acceleration(acceleration)
{
}

Entity::Entity(Point position, Point velocity, Point acceleration) :
    position(position), velocity(velocity), acceleration(acceleration)
{
}

void Entity::loadData()
{

}

void Entity::draw()
{

}
