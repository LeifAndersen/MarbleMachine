#ifndef BUTTON_H
#define BUTTON_H

#include "drawable.h"

enum ButtonType { PLAY, PAUSE, MENU };

class Button : public Drawable
{
public:
    Button(ButtonType buttonType);
    static void loadData();
    virtual void draw();
private:
    static std::vector<int> verts;
    static std::vector<int> triangle_faces;
    ButtonType buttonType;
};

#endif // BUTTON_H
