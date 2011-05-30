#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "include_opengl.h"

#include <vector>
#include <string>

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
    virtual void loadMVMatrix();
    Matrix mvMatrix;
};

#endif // DRAWABLE_H
