#ifndef BUTTON_H
#define BUTTON_H

#include "drawable.h"

// State
#define BUTTON_STATE_UP 0
#define BUTTON_STATE_DOWN 1
#define BUTTON_STATE_HOVER 2

#define BUTTON_STATES 3

struct button_verts_t
{
    DrawablePoint corners[4];
};

class Button : public Drawable
{
public:
    Button();
    ~Button();
    Button(const Button & other);
    Button & operator =(const Button & other);

    float x, y, widthHalf, heightHalf;

    unsigned int state;
    pthread_mutex_t stateMutex;

    button_verts_t texCoords[BUTTON_STATES];

    virtual void loadMVMatrix();

};

#endif // BUTTON_H
