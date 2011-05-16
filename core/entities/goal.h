#ifndef GOAL_H
#define GOAL_H

#include "entity.h"

class Goal : public Entity
{
public:
    Goal();
    static void loadData();
    virtual void draw();
};

#endif // GOAL_H
