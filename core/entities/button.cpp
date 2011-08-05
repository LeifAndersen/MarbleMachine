#include "button.h"

Button::Button() :
    state(BUTTON_STATE_UP),
    buttonOnScreen(false)
{

}

void Button::loadMVMatrix()
{
    mvMatrix.loadIdentity();
    mvMatrix.translate(x, y, 1);
    mvMatrix.scale(widthHalf, heightHalf, 1);
}
