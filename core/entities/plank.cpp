#include "include_opengl.h"
#include "plank.h"

using namespace std;

Plank::Plank()
{
}

void Plank::loadMVMatrix()
{
    mvMatrix.loadIdentity();
    mvMatrix.translate(position.x, position.y, position.z);
    mvMatrix.rotate(rotation, 0, 0, 1);
    mvMatrix.scale(length, width, 1);
}

std::vector<DrawablePoint> & Plank::getVerts()
{
    return verts;
}

std::vector<GLushort> & Plank::getIndices()
{
    return indices;
}

vector<DrawablePoint> Plank::verts;
vector<GLushort> Plank::indices;
