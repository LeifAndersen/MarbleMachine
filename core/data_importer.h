#ifndef DATA_IMPORTER_H
#define DATA_IMPORTER_H

#include <string>
#include "include_opengl.h"
#include "drawable.h"

#define UNCOMPRESSED 0
#define ETC_COMPRESSED 1

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

    /**
      *  Load the textures into the game state.
      */
    void loadTextures(unsigned int compressionType);

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

    /**
      * Input the texture data
      *
      * path:   The path to read in.
      * pixels: The place to put the data for the pixels.
      */
    static void parseETCCompressedTexData(const std::string & path,
                             std::vector<GLubyte> & pixels);

    /**
      * Input the texture data
      *
      * path:   The path to read in.
      * pixels: The place to put the data for the pixels.
      */
    static void parseTexData(const std::string & path,
                             std::vector<GLubyte> & pixels);

};

#endif // DATA_IMPORTER_H
