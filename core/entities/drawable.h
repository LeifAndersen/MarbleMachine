#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "include_opengl.h"

#include <vector>
#include <string>
#include <pthread.h>

#include "point.h"
#include "matrix.h"

struct DrawablePoint
{
    GLfloat x, y, z;
    GLfloat nx, ny, nz;
    GLfloat u, v;
};

struct DrawableColor
{
    GLubyte r, g, b;
};

class Drawable
{
public:
    Drawable();
    ~Drawable();
    Drawable & operator =(const Drawable & other);
    Drawable(const Drawable & other);

    Matrix mvMatrix;
    pthread_mutex_t mvMatrixMutex;

    virtual void loadMVMatrix();
};

#endif // DRAWABLE_H
