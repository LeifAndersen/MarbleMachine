#include "sphere.h"

using namespace std;

Sphere::Sphere()
{
    rotation = 0;
    position.x = position.y = position.z = 0;
    velocity.x = velocity.y = velocity.z = 0;
    acceleration.x = acceleration.y = acceleration.z = 0;
}

void Sphere::loadMVMatrix()
{
    mvMatrix.loadIdentity();
    mvMatrix.rotate(rotation, 0, 0, 1);
}

vector<DrawablePoint> Sphere::verts;
vector<GLushort> Sphere::indices;
