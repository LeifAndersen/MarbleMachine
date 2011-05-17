#ifndef COLLISIONGRID_H
#define COLLISIONGRID_H

#include "plank.h"
#include "cannon.h"

class CollisionGrid
{
public:
    /**
      * Constructor for this data structure
      *
      * Input:
      *     partitionSize: is the width of the squares of the grid.
      *     xSize: the max x dimmension from (0, 0)
      *     ySize: the max y dimmension from (0, 0)
      */
    collision_grid(int partitionSize, int xSize, int ySize);

    /**
      * Adda a plank to the grid
      *
      * Input:
      *     plank: reference to the plank to add.  YAY.
      */
    void addPlank(Plank & plank);

    /**
      * Add a cannon to the grid
      *
      * Input:
      *     plank: reference to the cannon to add.
      */
    void addCannon(Cannon & cannon);

    /**
      * Remove a plank from the grid
      *
      * Input:
      *     plank: reference to the plank to remove.
      */
    void removePlank(Plank & plank);

    /**
      * Remove a cannon from the grid
      *
      * Input:
      *     plank: reference to the cannon to remove.
      */
    void removeCannon(Cannon & cannon);

    /**
      * Get all the planks near the coordinates
      *
      * Input:
      *     x: x coordinate
      *     y: y coordinate
      */
    std::vector<Plank &> getPlanks(float x, float y);

    /**
      * Get all the cannons near the coordinates
      *
      * Input:
      *     x: x coordinate
      *     y: y coordinate
      */
    std::vector<Plank &> getCannons(float x, float y);

};

#endif // COLLISIONGRID_H
