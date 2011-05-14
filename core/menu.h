#ifndef MENU_H
#define MENU_H

class GameState;

class Menu
{
public:
    Menu(GameState & state);
private:
    GameState & state;
};

#endif // MENU_H
