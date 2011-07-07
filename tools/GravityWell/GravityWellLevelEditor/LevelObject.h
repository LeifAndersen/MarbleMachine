#ifndef LEVELOBJECT_H
#define LEVELOBJECT_H

#include "Point.h"

// This is the parent class that contains basic fields for every object in the level.
class LevelObject
{
public:
    LevelObject(unsigned long id);

    // Position
    float x;
    float y;
    //float z; // Is this necessary?

    // Orientation
    float rotation;

    // Velocity
    Point velocity;

    // Mass
    float mass;

    // ID
    unsigned long id;

};

#endif // LEVELOBJECT_H
