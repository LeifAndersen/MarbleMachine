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
    body.push_back(DrawablePoint());
    body[0].x = 0.0f;
    body[0].y = 0.5f;
    body[0].z = 0.0f;
    body.push_back(DrawablePoint());
    body[1].x = -0.5f;
    body[1].y = -0.5f;
    body[1].z = 0.0f;
    body.push_back(DrawablePoint());
    body[2].x = 0.5f;
    body[2].y = -0.5f;
    body[3].z = 0.0f;

    // Then prepare an opengl buffer for the data
    glGenBuffers(1, buffers);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, body.size()*sizeof(DrawablePoint), &(body[0]), GL_STATIC_DRAW);
}

void Sphere::draw()
{
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glEnableVertexAttribArray(gvPositionHandle);
    glVertexAttribPointer(gvPositionHandle, 3, GL_FLOAT, GL_FALSE, sizeof(DrawablePoint), 0);
    //glDrawElements(GL_TRIANGLES, 3, GL_FLOAT, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

vector<DrawablePoint> Sphere::body;

GLuint Sphere::buffers[1];

GLuint Sphere::gvPositionHandle;
