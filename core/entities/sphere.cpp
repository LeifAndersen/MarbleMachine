#include "sphere.h"

using namespace std;

Sphere::Sphere()
{
}

void Sphere::loadData(GLuint gvPositionHandle)
{
    // Set up the attrib locations
    Sphere::gvPositionHandle = gvPositionHandle;

    // Prepare an opengl buffer for the data,
    // assume that data has already been loaded
    glGenBuffers(2, buffers);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, verts.size()*sizeof(DrawablePoint), &(verts[0]), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(GLushort), &(indices[0]), GL_STATIC_DRAW);
}

void Sphere::draw()
{
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glEnableVertexAttribArray(gvPositionHandle);
    glVertexAttribPointer(gvPositionHandle, 3, GL_FLOAT, GL_FALSE, sizeof(DrawablePoint), 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);
}

vector<DrawablePoint> Sphere::verts;
vector<GLushort> Sphere::indices;

GLuint Sphere::buffers[2];

GLuint Sphere::gvPositionHandle;
