#ifndef ENTITY_H
#define ENTITY_H

#include<vector>

class Entity
{
public:
    Entity();
    virtual void draw();
private:
    std::vector<int> verts;
    std::vector<int> triangle_faces;
};

#endif // ENTITY_H
