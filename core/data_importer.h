#ifndef DATA_IMPORTER_H
#define DATA_IMPORTER_H

#include <string>
#include "include_opengl.h"
#include "drawable.h"

#include "objLoader.h"

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
    /**
      * Copy data from an obj
      */
    void cpyData(objLoader & loader,
                 std::vector<DrawablePoint> & verts,
                 std::vector<GLushort> & indices);
    GameState & state;
};

#endif // DATA_IMPORTER_H
