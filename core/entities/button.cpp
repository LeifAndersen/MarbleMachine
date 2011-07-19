#include "button.h"

Button::Button()
{

}

void Button::loadMVMatrix()
{
    mvMatrix.loadIdentity();
    mvMatrix.translate(x, y, 1);
    mvMatrix.scale(widthHalf, heightHalf, 1);
}
