#ifndef LEVELOBJECT_H
#define LEVELOBJECT_H

// This is the parent class that contains basic fields for every object in the level.
class LevelObject
{
public:
    LevelObject(unsigned long id, int type);

    // Position
    double xPos;
    double yPos;
    //double z; // Is this necessary?

    // Orientation
    double rotation;

    // Mass
    double mass;

    // ID
    unsigned long id;

    // Type
    int type;

};

#endif // LEVELOBJECT_H
