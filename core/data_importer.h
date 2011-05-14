#ifndef DATA_IMPORTER_H
#define DATA_IMPORTER_H

class GameState;

class DataImporter
{
public:
    DataImporter(GameState & state);
private:
    GameState & state;
};

#endif // DATA_IMPORTER_H
