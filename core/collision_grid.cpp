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
CollisionGrid::CollisionGrid(int _partitionSize, float xSize,
                             float ySize, float zSize)
{
    int xNodes = ceilf(xSize / _partitionSize);
    int yNodes = ceilf(ySize / _partitionSize);
    int zNodes = ceilf(zSize / _partitionSize);

    partitionSize = _partitionSize;

    grid.reserve(xNodes);

    for (int i = 0; i < xNodes; i++) {
        grid.push_back(vector<vector<GridNode> >());
        grid[i].reserve(yNodes);
        for(int j = 0; j < yNodes; j++) {
            grid[i].push_back(vector<GridNode>());
            grid[i][j].reserve(zNodes);
            for(int k = 0; k < zNodes; k++) {
                grid[i][j].push_back(GridNode());
            }
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
void CollisionGrid::rebuildGrid(int _partitionSize, float xSize,
                                float ySize, float zSize)
{
    // First, throw out the old data
    grid.clear();

    // Then, construct the new grid
    int xNodes = ceilf(xSize / _partitionSize);
    int yNodes = ceilf(ySize / _partitionSize);
    int zNodes = ceilf(zSize / _partitionSize);

    partitionSize = _partitionSize;

    grid.reserve(xNodes);

    for (int i = 0; i < xNodes; i++) {
        grid.push_back(vector<vector<GridNode> >());
        grid[i].reserve(yNodes);
        for(int j = 0; j < yNodes; j++) {
            grid[i].push_back(vector<GridNode>());
            grid[i][j].reserve(zNodes);
            for(int k = 0; k < zNodes; k++) {
                grid[i][j].push_back(GridNode());
            }
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
    int psuedoradius = sqrt(pow(plank->width / 2, 2)
                            + pow(plank->length / 2, 2)
                            + pow(plank->height / 2, 2));
    int x = 0;
    int y = 0;
    int z = 0;

    for (vector<vector<vector<GridNode> > >::iterator i = grid.begin(); i != grid.end(); i++, x++) {
        for(vector<vector<GridNode> >::iterator j = i->begin(); j != i->end(); j++, y++) {
            for(vector<GridNode>::iterator k = j->begin(); k != j->end(); k++, z++) {
                if (collide(x, y, z, psuedoradius, plank->position)) {
                    k->planks.push_back(plank);
                }
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
    int psuedoradius = sqrt(pow(cannon->width / 2, 2)
                            + pow(cannon->length / 2, 2)
                            + pow(cannon->height / 2, 2));
    int x = 0;
    int y = 0;
    int z = 0;

    for (vector<vector<vector<GridNode> > >::iterator i = grid.begin(); i != grid.end(); i++, x++) {
        for(vector<vector<GridNode> >::iterator j = i->begin(); j != i->end(); j++, y++) {
            for(vector<GridNode>::iterator k = j->begin(); k != j->end(); k++, z++) {
                if (collide(x, y, z, psuedoradius, cannon->position)) {
                    k->cannons.push_back(cannon);
                }
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
void CollisionGrid::removePlank(Plank * plank)
{
    for (vector<vector<vector<GridNode> > >::iterator i = grid.begin(); i != grid.end(); i++) {
        for(vector<vector<GridNode> >::iterator j = i->begin(); j != i->end(); j++) {
            for(vector<GridNode>::iterator k = j->begin(); k != j->end(); k++) {
                for (std::list<Plank *>::iterator m = k->planks.begin(); m != k->planks.end(); m++) {
                    if (*m == plank) {
                        k->planks.erase(m);
                        break;
                    }
                }
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
void CollisionGrid::removeCannon(Cannon * cannon)
{
    for (vector<vector<vector<GridNode> > >::iterator i = grid.begin(); i != grid.end(); i++) {
        for(vector<vector<GridNode> >::iterator j = i->begin(); j != i->end(); j++) {
            for(vector<GridNode>::iterator k = j->begin(); k != j->end(); k++) {
                for (list<Cannon *>::iterator m = k->cannons.begin(); m != k->cannons.end(); m++) {
                    if (*m == cannon) {
                        k->cannons.erase(m);
                        break;
                    }
                }
            }
        }
    }
}

/**
  * Get all the planks near the coordinates
  *
  * Input:
  *     planks: a reference to the list to fill
  *     x: x coordinate
  *     y: y coordinate
  *     z: z coordinate
  */
std::list<Plank *> & CollisionGrid::getPlanks(list<Plank *> & planks,
                                              float x, float y, float z)
{
    int floorX = (int)floorf(x);
    int floorY = (int)floorf(y);
    int floorZ = (int)floorf(z);

    unsigned int gridX = floorX - (floorX % partitionSize);
    unsigned int gridY = floorY - (floorY % partitionSize);
    unsigned int gridZ = floorZ - (floorZ % partitionSize);

    unsigned int startX = 0;
    unsigned int endX = 0;
    unsigned int startY = 0;
    unsigned int endY = 0;
    unsigned int startZ = 0;
    unsigned int endZ = 0;

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

    if(gridZ <= 0) {
        startZ = 0;
    } else {
        startZ = gridZ - 1;
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

    if(gridZ >= grid[0][0].size() - 1) {
        endZ = grid[0][0].size() - 1;
    } else {
        endZ = gridZ + 1;
    }

    for(unsigned int i = startX; i <= endX; i++) {
        for(unsigned int j = startY; j <= endY; j++) {
            for(unsigned int k = startZ; k <= endZ; k++) {
                GridNode gd = grid[i][j][k];
                for(list<Plank *>::iterator iter = gd.planks.begin();
                    iter != gd.planks.end(); iter++) {
                    planks.push_back(*iter);
                }
            }
        }
    }

    return planks;
}

/**
  * Get all the cannons near the coordinates
  *
  * Input:
  *     cannons: A reference to the list to fill
  *     x: x coordinate
  *     y: y coordinate
  *     z: z coordinate
  */
std::list<Cannon *> & CollisionGrid::getCannons(list<Cannon *> & cannons,
                                                float x, float y, float z)
{
    int floorX = (int)floorf(x);
    int floorY = (int)floorf(y);
    int floorZ = (int)floorf(z);

    unsigned int gridX = floorX - (floorX % partitionSize);
    unsigned int gridY = floorY - (floorY % partitionSize);
    unsigned int gridZ = floorZ - (floorZ % partitionSize);

    unsigned int startX = 0;
    unsigned int endX = 0;
    unsigned int startY = 0;
    unsigned int endY = 0;
    unsigned int startZ = 0;
    unsigned int endZ = 0;

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

    if(gridZ <= 0) {
        startZ = 0;
    } else {
        startZ = gridZ - 1;
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

    if(gridZ >= grid[0][0].size() - 1) {
        endZ = grid[0][0].size() - 1;
    } else {
        endZ = gridZ + 1;
    }

    for(unsigned int i = startX; i <= endX; i++) {
        for(unsigned int j = startY; j <= endY; j++) {
            for(unsigned int k = startZ; k <= endZ; k++) {
                GridNode gd = grid[i][j][k];
                for(list<Cannon *>::iterator iter = gd.cannons.begin();
                    iter != gd.cannons.end(); iter++) {
                    cannons.push_back(*iter);
                }
            }
        }
    }

    return cannons;
}


// TODO FIX! (currently it ignores third dimension
bool CollisionGrid::collide(int x, int y, int z, int r, const Point & obj)
{
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
