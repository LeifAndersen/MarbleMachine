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

    /**:strin
      * Parse an obj file to load the data
      */
    void parseData(std::string path, std::vector<DrawablePoint> & verts,
                   std::vector<GLushort> & indices);
};

#endif // DATA_IMPORTER_H
