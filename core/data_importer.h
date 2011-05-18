#ifndef DATA_IMPORTER_H
#define DATA_IMPORTER_H

class GameState;

class DataImporter
{
public:
    DataImporter(GameState & state);

    /**
      * Import a level from the file/
      */
    void importLevel(unsigned int level);

private:
    GameState & state;
};

#endif // DATA_IMPORTER_H
