#ifndef LEVELOBJECT_H
#define LEVELOBJECT_H

#include "Point.h"

// This is the parent class that contains basic fields for every object in the level.
class LevelObject
{
public:
    LevelObject(unsigned long id);

    // Position
    double xPos;
    double yPos;
    //double z; // Is this necessary?

    // Size
    double radius;

    // Orientation
    double rotation;

    // Velocity
    Point velocity;

    // Mass
    double mass;

    // ID
    unsigned long id;

};

#endif // LEVELOBJECT_H
