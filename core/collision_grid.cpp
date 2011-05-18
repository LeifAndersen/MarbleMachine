#include "collision_grid.h"
#include "math.h"
#include "stdlib.h"

bool CollisionGrid::collide(int x, int y, int r, Point obj) {
    int wid = (x * partitionSize) / 2;
    int hei = (y * partitionSize) / 2;

    int distx = abs(obj.x - (x * partitionSize));
    int disty = abs(obj.y - (y * partitionSize));

    if (distx > (wid + r)) { return false; }
    if (disty > (hei + r)) { return false; }

    if (distx <= (wid)) { return true; }
    if (disty <= (hei)) { return true; }

    int cornerDistance_sq = (distx - wid) * (distx - wid) +
        (disty - hei) * (disty - hei);

    return (cornerDistance_sq <= (r * r));
}

/**
  * Constructor for this data structure
  *
  * Input:
  *     partitionSize: is the width of the squares of the grid.
  *     xSize: the max x dimmension from (0, 0)
  *     ySize: the max y dimmension from (0, 0)
  */
CollisionGrid::CollisionGrid(int _partitionSize, int xSize, int ySize) {
    int xNodes = ceil(xSize / _partitionSize);
    int yNodes = ceil(ySize / _partitionSize);

    partitionSize = _partitionSize;

    grid.reserve(xNodes);

    for (int i = 0; i < xNodes; i++) {
        grid[i].reserve(yNodes);
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
std::vector<Plank *> CollisionGrid::getPlanks(float x, float y) {
    std::list<Plank *> planks;

    int gridX = (int)floor(x) - ((int)floor(x) % partitionSize);
    int gridY = (int)floor(y) - ((int)floor(y) % partitionSize);

    int startX = 0;
    int endX = 0;
    int startY = 0;
    int endY = 0;

    if(gridX == 0) {
        startX = 0;
    } else {
        startX = gridX - 1;
    }

    if(gridY == 0) {
        startY = 0;
    } else {
        startY = gridY - 1;
    }

    if((gridX + 1) % grid.size() == 0) {
        endX = gridX;
    } else {
        endX = (gridX + 1) % grid.size();
    }

    if((gridY + 1) % grid[0].size() == 0) {
        endY = gridY;
    } else {
        endY = (gridY + 1) % grid[0].size();
    }

    for(int i = startX; i <= endX; i++) {
        for(int j = startY; j <= endY; j++) {
            planks.splice(grid[i][j].planks.begin(), grid[i][j].planks);
        }
    }
}

/**
  * Get all the cannons near the coordinates
  *
  * Input:
  *     x: x coordinate
  *     y: y coordinate
  */
std::vector<Plank *> CollisionGrid::getCannons(float x, float y) {
    std::list<Cannon *> cannons;

    int gridX = (int)floor(x) - ((int)floor(x) % partitionSize);
    int gridY = (int)floor(y) - ((int)floor(y) % partitionSize);

    int startX = 0;
    int endX = 0;
    int startY = 0;
    int endY = 0;

    if(gridX == 0) {
        startX = 0;
    } else {
        startX = gridX - 1;
    }

    if(gridY == 0) {
        startY = 0;
    } else {
        startY = gridY - 1;
    }

    if((gridX + 1) % grid.size() == 0) {
        endX = gridX;
    } else {
        endX = (gridX + 1) % grid.size();
    }

    if((gridY + 1) % grid[0].size() == 0) {
        endY = gridY;
    } else {
        endY = (gridY + 1) % grid[0].size();
    }

    for(int i = startX; i <= endX; i++) {
        for(int j = startY; j <= endY; j++) {
            cannons.splice(grid[i][j].cannons.begin(), grid[i][j].cannons);
        }
    }
}
