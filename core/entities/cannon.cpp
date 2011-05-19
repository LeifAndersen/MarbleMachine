#include "cannon.h"

using namespace std;

Cannon::Cannon()
{
}

void Cannon::loadData()
{
    glGenBuffers(1, &buffer);
}

void Cannon::draw()
{
    // Drawable::loadData("cannon", 1, &buffer, verts);
}

GLuint Cannon::buffer = 0;


vector<Point> Cannon::verts;
