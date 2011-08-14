#include "sphere.h"

using namespace std;

Sphere::Sphere() :
    radius(1)
{
}

Sphere::~Sphere()
{
}

Sphere::Sphere(const Sphere &other) :
    Entity(other),
    radius(other.radius)
{
}

Sphere & Sphere::operator =(const Sphere &other)
{
    Entity * super = this;
    (*super) = other;
    radius = other.radius;
    return *this;
}

void Sphere::loadMVMatrix()
{
    mvMatrix.loadIdentity();
    mvMatrix.translate(position.x, position.y, position.z);
    mvMatrix.rotate(rotation.x, 1, 0, 0);
    mvMatrix.rotate(rotation.y, 0, 1, 0);
    mvMatrix.rotate(rotation.z, 0, 0, 1);
    mvMatrix.scale(radius, radius, radius);
}
