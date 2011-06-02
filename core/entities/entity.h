#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>
#include "point.h"
#include "drawable.h"

#define MOVE_OBJ 0
#define ROTATE_OBJ 1
#define PLACE_OBJ 2

class Entity : public Drawable
{
public:
    Entity();
    Entity(bool isMovable);
    Entity(Point position);
    Entity(Point position, bool isMovable);
    Entity(Point position, Point velocity);
    Entity(Point position, Point velocity, Point acceleration);
    static void loadData();
    virtual void draw();

    Point position;
    Point velocity;
    Point acceleration;

    float rotation;
    Point normal; // TODO -- make sure the normal is always the side that is facing rotation + 90º
                  // based on the assumption that a plank lying flat has a rotation of 0º

    float mass;
    bool isMovable;
private:
    static std::vector<int> verts;
    static std::vector<int> triangle_faces;
    unsigned int state;
};

#endif // ENTITY_H
