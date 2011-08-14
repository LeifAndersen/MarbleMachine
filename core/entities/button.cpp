#include "button.h"

#include <assert.h>

Button::Button() :
    state(BUTTON_STATE_UP),
    buttonOnScreen(false)
{
    assert(!pthread_mutex_init(&stateMutex, NULL));
}

Button::~Button()
{
    assert(!pthread_mutex_destroy(&stateMutex));
}

Button::Button(const Button &other) :
    Drawable(other),
    x(other.x),
    y(other.y),
    widthHalf(other.widthHalf),
    heightHalf(other.heightHalf),
    state(BUTTON_STATE_UP),
    buttonOnScreen(false)
{
    assert(!pthread_mutex_init(&stateMutex, NULL));
    for(unsigned int i = 0; i < BUTTON_STATES; i++) {
        texCoords[i] = other.texCoords[i];
    }
}

Button & Button::operator =(const Button &other)
{
    Drawable * super = this;
    (*super) = other;
    state = other.state;
    buttonOnScreen = other.buttonOnScreen;
    x = other.x;
    y = other.y;
    widthHalf = other.widthHalf;
    heightHalf = other.heightHalf;
    for(unsigned int i = 0; i < BUTTON_STATES; i++) {
        texCoords[i] = other.texCoords[i];
    }
    return *this;
}

void Button::loadMVMatrix()
{
    mvMatrix.loadIdentity();
    mvMatrix.translate(x, y, 1);
    mvMatrix.scale(widthHalf, heightHalf, 1);
}
