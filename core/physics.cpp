#include <list>
#include <cstdlib>
#include <cmath>

#include "physics.h"
#include "game_state.h"
#include "os_calls.h"

using namespace std;

#define GRAVITY -1
#define TERMINAL_VELOCITY -10

Physics::Physics(GameState & state) : state(state)
{
}

void Physics::update(float timeDelta)
{
    if (state.marbleInCannon) {
        if (state.timeInCannon < state.CANNON_FIRE_TIME) {
            state.timeInCannon += timeDelta;
            return;
        } else {
            // Fire since the time has elapsed.
            state.marble.position = state.firingCannon->position;
            state.marble.velocity = state.firingCannon->normal * state.CANNON_FIRE_VELOCITY;
            state.marbleInCannon = false;
        }
    }
    // First, move the marble
    if(state.marble.velocity.y > TERMINAL_VELOCITY) {
        state.marble.acceleration.x = 0;
        state.marble.acceleration.y = GRAVITY;
        state.marble.velocity += state.marble.acceleration*timeDelta;
    }
    state.marble.position += state.marble.velocity*timeDelta;

    // Then, check for collisions
    // First, broad check to see what's in the vecinity
    list<Plank *> planks;
    state.grid.getPlanks(planks,
                         state.marble.position.x,
                         state.marble.position.y,
                         state.marble.position.z);
    list<Cannon *> cannons;
    state.grid.getCannons(cannons,
                          state.marble.position.x,
                          state.marble.position.y,
                          state.marble.position.z);

    // Second, more precice check for close objects
    for(list<Cannon *>::iterator i = cannons.begin(); i != cannons.end(); i++) {
        Point alignedMarblePos;

        // Axis align the problem
        if ((*i)->rotation != 0) {
            float rectRot = ((*i)->rotation * M_PI) / 180;
            alignedMarblePos.x = cos(rectRot) * (state.marble.position.x - (*i)->position.x)
                                      - sin(rectRot) * (state.marble.position.y -
                                                        (*i)->position.y) + (*i)->position.x;
            alignedMarblePos.y = sin(rectRot) * (state.marble.position.x - (*i)->position.x)
                                      + cos(rectRot) * (state.marble.position.y -
                                                        (*i)->position.y) + (*i)->position.y;
        }

        if (circleSquareCollide(state.marble.radius, alignedMarblePos, (*i)->length,
                                (*i)->width, (*i)->position)) {
            state.marbleInCannon = true;
            state.timeInCannon = 0;
            state.firingCannon = *i;
        }
    }
    for(list<Plank *>::iterator i = planks.begin(); i != planks.end(); i++) {
        Point alignedMarblePos;

        // Axis align the problem
        if ((*i)->rotation != 0) {
            float rectRot = ((*i)->rotation * M_PI) / 180;
            alignedMarblePos.x = cos(rectRot) * (state.marble.position.x - (*i)->position.x)
                                      - sin(rectRot) * (state.marble.position.y -
                                                        (*i)->position.y) + (*i)->position.x;
            alignedMarblePos.y = sin(rectRot) * (state.marble.position.x - (*i)->position.x)
                                      + cos(rectRot) * (state.marble.position.y -
                                                        (*i)->position.y) + (*i)->position.y;
        } else {
            alignedMarblePos.x = state.marble.position.x;
            alignedMarblePos.y = state.marble.position.y;
        }

        if (circleSquareCollide(state.marble.radius, alignedMarblePos, (*i)->length,
                                (*i)->width, (*i)->position)) {
            int side = 0;
            float overlap;

            // Find the side of the plank that the marble is on
            if ((state.marble.radius + (*i)->length / 2) >
                fabs(alignedMarblePos.x - (*i)->position.x)) {
                // it is on the top or bottom.
                if (alignedMarblePos.y > (*i)->position.y) {
                    side = topSide;
                } else {
                    side = bottomSide;
                }
                overlap = fabs(alignedMarblePos.y - (*i)->position.y) - state.marble.radius;
            } else {
                // it is on the right or left
                if (alignedMarblePos.x > (*i)->position.x) {
                    side = rightSide;
                } else {
                    side = leftSide;
                }
                overlap = fabs(alignedMarblePos.x - (*i)->position.x) - state.marble.radius;
            }

            // Reflect velocity. (form here on, we do not need to be axis aligned)
            Point sideNormal;
            switch (side) {
            case topSide:
                sideNormal = (*i)->normal;
                break;
            case rightSide:
                sideNormal.x = (*i)->normal.y * -1;
                sideNormal.y = (*i)->normal.x;
                break;
            case bottomSide:
                sideNormal.x = (*i)->normal.x * -1;
                sideNormal.y = (*i)->normal.y * -1;
                break;
            case leftSide:
                sideNormal.x = (*i)->normal.y;
                sideNormal.y = (*i)->normal.x * -1;
                break;
            }

            state.marble.velocity = reflect(state.marble.velocity, sideNormal);

            // Move marble along the normal of the plank so that it is no longer colliding.
            state.marble.position += sideNormal * /*overlap **/ 1.001; // Note the ARBITRARY fudge factor to make sure collisions aren't repeated.
        }
    }
    // If it's reached the goal, you win
}

bool Physics::circleSquareCollide(float cirR, Point cirPos, float rectW, float rectH,
                                  Point rectPos) {
    float cirDistX = fabs(cirPos.x - rectPos.x - rectW/2);
    float cirDistY = fabs(cirPos.y - rectPos.y - rectH/2);

    if (cirDistX > (rectW/2 + cirR)) { return false; }
    if (cirDistY > (rectH/2 + cirR)) { return false; }

    if (cirDistX <= (rectW/2)) { return true; }
    if (cirDistY <= (rectH/2)) { return true; }

    float cornerDistance_sq = pow((cirDistX - rectW/2), 2) + pow((cirDistY - rectH/2), 2);

    return (cornerDistance_sq <= pow(cirR, 2));
}

Point Physics::reflect(Point incidence, Point surfaceNormal) {
    return incidence - surfaceNormal * (incidence * surfaceNormal * 2);
}
