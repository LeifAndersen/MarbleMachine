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
      * Import a zone from the appropriate file.
      */
    void loadZone(unsigned int zone);

    /**
      * Import a level from the appropriate file
      */
    void loadLevel(unsigned int zone, unsigned int level);

    /**
      * Fill up the mesh data, texture data, etc.
      */
    void loadDrawables();

    /**
      *  Load the textures into the game state.
      */
    void loadTextures();

private:
    GameState & state;

    /**
      * Read in the file specified by the path.
      *
      * path:    The path to open.
      * verts:   The location for the verts.
      * indices: The location for the indices.
      */
    static void parseData(const std::string & path,
                          std::vector<DrawablePoint> & verts,
                          std::vector<GLushort> & indices);
};

#endif // DATA_IMPORTER_H
