#ifndef DATA_IMPORTER_H
#define DATA_IMPORTER_H

#include <string>
#include "include_opengl.h"
#include "drawable.h"
#include "button.h"

class GameState;

class DataImporter
{
public:
    DataImporter(GameState & state);

    /**
      * Import the main galactic menu.
      */
    void loadGalaxy();

    /**
      * Import a sector from the appropriate file.
      */
    void loadSector(unsigned int sector);

    /**
      * Import a level from the appropriate file
      */
    void loadLevel(unsigned int sector, unsigned int level);

    /**
      * Fill up the mesh data, texture data, etc.
      */
    void loadDrawables();

    /**
      *  Load the textures into the game state.
      */
    void loadTextures();

    /**
      * Load the sounds for the game.  It's few enough sounds
      * we can load it up once at the begining.
      *
      */
    void loadSounds();

    /**
      * Save the game state
      */
    void saveGame();

    /**
      * Load the game state, or if there is no save, load the default.
      */
    void loadGame();

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
      * Load the data for a button.
      *
      * path:   The path for the file containing data for the button.
      * button: The button to load the data into.
      */
    static void loadButton(const std::string & path,
                           Button & button);

    /**
      * Load the default game.
      */
    void loadDefaultGame();
};

#endif // DATA_IMPORTER_H
