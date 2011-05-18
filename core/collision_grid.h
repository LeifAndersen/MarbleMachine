#ifndef COLLISIONGRID_H
#define COLLISIONGRID_H

#include "plank.h"
#include "cannon.h"
#include "point.h"
#include "list"
#include "vector"

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
    CollisionGrid(int _partitionSize, int xSize, int ySize);

    /**
      * Throws out all existing data in the grid
      * And then constructs a new grid, with new paramaters.
      *
      * Input:
      *     partitionSize: is the width of the squares of the grid.
      *     xSize: the max x dimmension from (0, 0)
      *     ySize: the max y dimmension from (0, 0)
      */
    void rebuildGrid(int _partitionSize, int xSize, int ySize);

    /**
      * Adda a plank to the grid
      *
      * Input:
      *     plank: reference to the plank to add.  YAY.
      */
    void addPlank(Plank * plank);

    /**
      * Add a cannon to the grid
      *
      * Input:
      *     plank: reference to the cannon to add.
      */
    void addCannon(Cannon * cannon);

    /**
      * Remove a plank from the grid
      *
      * Input:
      *     plank: reference to the plank to remove.
      */
    void removePlank(Plank * plank);

    /**
      * Remove a cannon from the grid
      *
      * Input:
      *     plank: reference to the cannon to remove.
      */
    void removeCannon(Cannon * cannon);

    /**
      * Get all the planks near the coordinates
      *
      * Input:
      *     x: x coordinate
      *     y: y coordinate
      */
    std::list<Plank *> getPlanks(float x, float y);

    /**
      * Get all the cannons near the coordinates
      *
      * Input:
      *     x: x coordinate
      *     y: y coordinate
      */
    std::list<Cannon *> getCannons(float x, float y);

private:

    struct GridNode {
        std::list<Cannon *> cannons;
        std::list<Plank *> planks;
    };

    /**
      * Do circle sqaure collision for the grid square at x and y
      *
      * Input:
      *     x: x coordinate of grid square
      *     y: y coordinate of grid square
      *     r: radius of circle
      *     obj: the position of the circle
      */
    bool collide(int x, int y, int r, Point obj);

    int partitionSize;
    std::vector<std::vector<GridNode> > grid;
};

#endif // COLLISIONGRID_H
