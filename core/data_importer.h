#ifndef DATA_IMPORTER_H
#define DATA_IMPORTER_H

#include <string>
#include "include_opengl.h"
#include "drawable.h"

class GameState;

class DataImporter
{
public:
    DataImporter(GameState & state);

    /**
      * Import a level from the appropriate file
      */
    void loadLevel(unsigned int level);

    /**
      * Fill up the mesh data, texture data, etc.
      */
    void loadDrawables();
private:
    GameState & state;
};

#endif // DATA_IMPORTER_H
