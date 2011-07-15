#ifndef BUTTON_H
#define BUTTON_H

#include "drawable.h"

#define STANDARD_BUTTON 0
#define SPAWNER_BUTTON 1

// State
#define STATE_UP 0
#define STATE_DOWN 1
#define STATE_HOVER 2

struct button_verts_t
{
    DrawablePoint corners[4];
};

class Button : public Drawable
{
public:
    Button();
    Button(unsigned int buttonType);

    float x, y, w, h;

    unsigned int state;

    button_verts_t texCoords;

    virtual void loadMVMatrix();

private:
    unsigned int buttonType;
};

#endif // BUTTON_H
