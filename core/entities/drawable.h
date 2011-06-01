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
    GLfloat r, g, b, a;
};

class Drawable
{
public:
    Drawable();

    Matrix mvMatrix;
    pthread_mutex_t mvMatrixMutex;

    virtual void loadMVMatrix();
    virtual std::vector<DrawablePoint> & getVerts();
    virtual std::vector<GLushort> & getIndices();
private:
    static std::vector<DrawablePoint> verts;
    static std::vector<GLushort> indices;
};

#endif // DRAWABLE_H
