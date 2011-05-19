#include <string>

#include "goal.h"

using namespace std;

Goal::Goal()
{

}

void Goal::loadData()
{
    // Drawable::loadData("goal", 1, &buffer, verts);
}

void Goal::draw()
{

}

GLuint Goal::buffer = 0;

vector<Point> Goal::verts;
