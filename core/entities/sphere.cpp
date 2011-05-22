#include "sphere.h"

using namespace std;

Sphere::Sphere()
{
}

void Sphere::loadData(GLuint gvPositionHandle)
{
    // Set up the attrib locations
    Sphere::gvPositionHandle = gvPositionHandle;

    // Read in the data
    // TODO

    // Testing vector
    verts.push_back(DrawablePoint());
    verts[0].x = 0.0f;
    verts[0].y = 0.5f;
    verts[0].z = 0.0f;
    verts.push_back(DrawablePoint());
    verts[1].x = -0.5f;
    verts[1].y = -0.5f;
    verts[1].z = 0.0f;
    verts.push_back(DrawablePoint());
    verts[2].x = 0.5f;
    verts[2].y = -0.5f;
    verts[3].z = 0.0f;
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);

    // Then prepare an opengl buffer for the data
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
