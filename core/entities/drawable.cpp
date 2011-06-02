#include <pthread.h>
#include <cassert>

#include "drawable.h"

using namespace std;

Drawable::Drawable()
{
    assert(!pthread_mutex_init(&mvMatrixMutex, NULL));
}

void Drawable::loadMVMatrix()
{

}

std::vector<DrawablePoint> & Drawable::getVerts()
{
    return verts;
}

std::vector<GLushort> & Drawable::getIndices()
{
    return indices;
}

std::vector<DrawablePoint> Drawable::verts;
std::vector<GLushort> Drawable::indices;
