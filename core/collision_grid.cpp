#include "collision_grid.h"
#include "math.h"
#include "stdlib.h"
#include "os_calls.h"

using namespace std;

/**
  * Constructor for this data structure
  *
  * Input:
  *     partitionSize: is the width of the squares of the grid.
  *     xSize: the max x dimmension from (0, 0)
  *     ySize: the max y dimmension from (0, 0)
  */
CollisionGrid::CollisionGrid(int _partitionSize, float xSize, float ySize) {
    int xNodes = ceilf(xSize / _partitionSize);
    int yNodes = ceilf(ySize / _partitionSize);
    partitionSize = _partitionSize;

    grid.reserve(xNodes);

    for (int i = 0; i < xNodes; i++) {
        grid.push_back(vector<GridNode>());
        grid[i].reserve(yNodes);
        for(int j = 0; j < yNodes; j++) {
            grid[i].push_back(GridNode());
        }
    }
}

/**
  * Throws out all existing data in the grid
  * And then constructs a new grid, with new paramaters.
  *
  * Input:
  *     partitionSize: is the width of the squares of the grid.
  *     xSize: the max x dimmension from (0, 0)
  *     ySize: the max y dimmension from (0, 0)
  */
void CollisionGrid::rebuildGrid(int _partitionSize, float xSize, float ySize) {
    // First, throw out the old data
    grid.clear();

    // Then, construct the new grid
    int xNodes = ceil(xSize / _partitionSize);
    int yNodes = ceil(ySize / _partitionSize);

    partitionSize = _partitionSize;

    grid.reserve(xNodes);

    for (int i = 0; i < xNodes; i++) {
        grid.push_back(vector<GridNode>());
        grid[i].reserve(yNodes);
        for(int j = 0; j < yNodes; j++) {
            grid[i].push_back(GridNode());
        }
    }
}

/**
  * Add a plank to the grid
  *
  * Input:
  *     plank: pointer to the plank to add.  YAY.
  */
void CollisionGrid::addPlank(Plank * plank) {
    int psuedoradius = sqrt(pow(plank->position.x, 2) + pow(plank->position.y, 2));
    int x = 0;
    int y = 0;

    for (std::vector<std::vector<GridNode> >::iterator i = grid.begin(); i != grid.end(); i++, x++) {
        for(std::vector<GridNode>::iterator j = i->begin(); j != i->end(); j++, y++) {
            if (collide(x, y, psuedoradius, plank->position)) {
                j->planks.push_back(plank);
            }
        }
    }
}

/**
  * Add a cannon to the grid
  *
  * Input:
  *     plank: pointer to the cannon to add.
  */
void CollisionGrid::addCannon(Cannon * cannon) {
    int psuedoradius = sqrt(pow(cannon->position.x, 2) + pow(cannon->position.y, 2));
    int x = 0;
    int y = 0;

    for (std::vector<std::vector<GridNode> >::iterator i = grid.begin(); i != grid.end(); i++, x++) {
        for(std::vector<GridNode>::iterator j = i->begin(); j != i->end(); j++, y++) {
            if (collide(x, y, psuedoradius, cannon->position)) {
                j->cannons.push_back(cannon);
            }
        }
    }
}

/**
  * Remove a plank from the grid
  *
  * Input:
  *     plank: pointer to the plank to remove.
  */
void CollisionGrid::removePlank(Plank * plank) {
    std::list<Plank *>::iterator toRemove;
    bool remove = false;

    for (std::vector<std::vector<GridNode> >::iterator i = grid.begin(); i != grid.end(); i++) {
        for(std::vector<GridNode>::iterator j = i->begin(); j != i->end(); j++) {
            for (std::list<Plank *>::iterator k = j->planks.begin(); k != j->planks.end(); k++) {
                if ((*k) == plank) {
                    toRemove = k;
                    break;
                }
            }
            if (remove) {
                j->planks.erase(toRemove);
                remove = false;
            }
        }
    }
}

/**
  * Remove a cannon from the grid
  *
  * Input:
  *     plank: pointer to the cannon to remove.
  */
void CollisionGrid::removeCannon(Cannon * cannon) {
    std::list<Cannon *>::iterator toRemove;
    bool remove = false;

    for (std::vector<std::vector<GridNode> >::iterator i = grid.begin(); i != grid.end(); i++) {
        for(std::vector<GridNode>::iterator j = i->begin(); j != i->end(); j++) {
            for (std::list<Cannon *>::iterator k = j->cannons.begin(); k != j->cannons.end(); k++) {
                if ((*k) == cannon) {
                    toRemove = k;
                    break;
                }
            }
            if (remove) {
                j->cannons.erase(toRemove);
                remove = false;
            }
        }
    }
}

/**
  * Get all the planks near the coordinates
  *
  * Input:
  *     x: x coordinate
  *     y: y coordinate
  */
std::list<Plank *> CollisionGrid::getPlanks(float x, float y) {
    std::list<Plank *> planks;

    int floorX = (int)floorf(x);
    int floorY = (int)floorf(y);

    unsigned int gridX = floorX - (floorX % partitionSize);
    unsigned int gridY = floorY - (floorY % partitionSize);

    unsigned int startX = 0;
    unsigned int endX = 0;
    unsigned int startY = 0;
    unsigned int endY = 0;

    if(gridX <= 0) {
        startX = 0;
    } else {
        startX = gridX - 1;
    }

    if(gridY <= 0) {
        startY = 0;
    } else {
        startY = gridY - 1;
    }

    if(gridX >= grid.size() - 1) {
        endX = grid.size() - 1;
    } else {
        endX = gridX + 1;
    }

    if(gridY >= grid[0].size() - 1) {
        endY = grid[0].size() - 1;
    } else {
        endY = gridY + 1;
    }

    for(unsigned int i = startX; i <= endX; i++) {
        for(unsigned int j = startY; j <= endY; j++) {
            GridNode gd = grid[i][j];
            for(list<Plank *>::iterator i = gd.planks.begin();
                i != gd.planks.end(); i++) {
                planks.push_back(*i);
            }
        }
    }

    return planks;
}

/**
  * Get all the cannons near the coordinates
  *
  * Input:
  *     x: x coordinate
  *     y: y coordinate
  */
std::list<Cannon *> CollisionGrid::getCannons(float x, float y) {
    std::list<Cannon *> cannons;

    int floorX = (int)floorf(x);
    int floorY = (int)floorf(y);

    unsigned int gridX = floorX - (floorX % partitionSize);
    unsigned int gridY = floorY - (floorY % partitionSize);

    unsigned int startX = 0;
    unsigned int endX = 0;
    unsigned int startY = 0;
    unsigned int endY = 0;

    if(gridX <= 0) {
        startX = 0;
    } else {
        startX = gridX - 1;
    }

    if(gridY <= 0) {
        startY = 0;
    } else {
        startY = gridY - 1;
    }

    if(gridX >= grid.size() - 1) {
        endX = grid.size() - 1;
    } else {
        endX = gridX + 1;
    }

    if(gridY >= grid[0].size() - 1) {
        endY = grid[0].size() - 1;
    } else {
        endY = gridY + 1;
    }

    for(unsigned int i = startX; i <= endX; i++) {
        for(unsigned int j = startY; j <= endY; j++) {
            GridNode gd = grid[i][j];
            for(list<Cannon *>::iterator i = gd.cannons.begin();
                i != gd.cannons.end(); i++) {
                cannons.push_back(*i);
            }
        }
    }

    return cannons;
}

// now at the bottom
bool CollisionGrid::collide(int x, int y, int r, Point obj) {
    int wid = (x * partitionSize) / 2;
    int hei = (y * partitionSize) / 2;

    int distx = fabs(obj.x - (x * partitionSize));
    int disty = fabs(obj.y - (y * partitionSize));

    if (distx > (wid + r)) { return false; }
    if (disty > (hei + r)) { return false; }

    if (distx <= (wid)) { return true; }
    if (disty <= (hei)) { return true; }

    int cornerDistance_sq = (distx - wid) * (distx - wid) +
        (disty - hei) * (disty - hei);

    return (cornerDistance_sq <= (r * r));
}
