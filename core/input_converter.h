#ifndef INPUT_CONVERTER_H
#define INPUT_CONVERTER_H

#include "game_state.h"

class InputConverter
{
public:
    InputConverter(GameState & state);
private:
    GameState & state;
};

#endif // INPUT_CONVERTER_H
