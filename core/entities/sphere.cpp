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
    body.push_back(0.0f);
    body.push_back(0.0f);
    body.push_back(0.0f);
    body.push_back(0.0f);
    body.push_back(0.0f);
    body.push_back(-0.5f);
    body.push_back(-0.5f);
    body.push_back(0.0f);
    body.push_back(0.0f);
    body.push_back(0.0f);
    body.push_back(0.0f);
    body.push_back(0.0f);
    body.push_back(0.0f);
    body.push_back(0.5f);
    body.push_back(-0.5f);
    body.push_back(0.0f);
    body.push_back(0.0f);
    body.push_back(0.0f);
    body.push_back(0.0f);
    body.push_back(0.0f);
    body.push_back(0.0f);


    // Then prepare an opengl buffer for the data
    glGenBuffers(1, &buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, body.size()*sizeof(float), &(body[0]), GL_STATIC_DRAW);

}

void Sphere::draw()
{

}

vector<float> Sphere::body;

GLuint Sphere::buffers[1];
