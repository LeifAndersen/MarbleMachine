#include "sphere.h"

using namespace std;

Sphere::Sphere()
{
}

void Sphere::loadData()
{
    // First, read in the data
    // TODO

    // Testing vector
    body.push_back(0.0f);
    body.push_back(0.5f);
    body.push_back(0.0f);
    body.push_back(-0.5f);
    body.push_back(-0.5f);
    body.push_back(0.0f);
    body.push_back(0.5f);
    body.push_back(-0.5f);
    body.push_back(0.0f);

    body_size = body.size() / 2;

    // Then prepare an opengl buffer for the data
    glGenBuffers(1, buffers);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, body.size()*sizeof(float), &(body[0]), GL_STATIC_DRAW);
}

void Sphere::draw(GLuint vertex_attrib)
{
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glEnableVertexAttribArray(vertex_attrib);
    glVertexAttribPointer(vertex_attrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    //glDrawElements(GL_TRIANGLES, 3, GL_FLOAT, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);

}

vector<GLfloat> Sphere::body;

int Sphere::body_size;

GLuint Sphere::buffers[1];
