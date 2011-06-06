#include "sphere.h"

using namespace std;

Sphere::Sphere()
{
    rotation = 0;
    radius = 1;
    loadMVMatrix();
}

void Sphere::loadMVMatrix()
{
    mvMatrix.loadIdentity();
    mvMatrix.translate(position.x, position.y, position.z);
    mvMatrix.rotate(rotation, 0, 0, 1);
    mvMatrix.scale(radius, radius, radius);
}

std::vector<DrawablePoint> & Sphere::getVerts()
{
    return verts;
}

std::vector<GLushort> & Sphere::getIndices()
{
    return indices;
}

vector<DrawablePoint> Sphere::verts;
vector<GLushort> Sphere::indices;
