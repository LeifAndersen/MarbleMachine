#include "button.h"

Button::Button() : buttonType(STANDARD_BUTTON)
{

}

Button::Button(unsigned int buttonType) : buttonType(buttonType)
{
}

void Button::loadMVMatrix()
{
    mvMatrix.loadIdentity();
    mvMatrix.translate(x-(w/2),y-(w/2), 0);
    mvMatrix.scale(w, h, 1);
}
