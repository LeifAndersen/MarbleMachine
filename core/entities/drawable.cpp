#include <pthread.h>
#include <cassert>

#include "drawable.h"

using namespace std;

Drawable::Drawable()
{
    assert(!pthread_mutex_init(&mvMatrixMutex, NULL));
}

Drawable::~Drawable()
{
    assert(!pthread_mutex_destroy(&mvMatrixMutex));
}

Drawable::Drawable(const Drawable &other)
{
    assert(!pthread_mutex_init(&mvMatrixMutex, NULL));
    mvMatrix.matrix = other.mvMatrix.matrix;
}

Drawable & Drawable::operator =(const Drawable &other)
{
    mvMatrix.matrix = other.mvMatrix.matrix;
    return *this;
}

void Drawable::loadMVMatrix()
{
    mvMatrix.loadIdentity();
}
