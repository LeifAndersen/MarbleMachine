#include <string>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#include "data_importer.h"

#include "game_state.h"
#include "os_calls.h"

using namespace std;

DataImporter::DataImporter(GameState & state) : state(state)
{
}

void DataImporter::loadLevel(unsigned int level)
{

}

void DataImporter::loadDrawables()
{
    parseData("marble", state.marble.verts, state.marble.indices);
}

void DataImporter::parseData(string path, std::vector<DrawablePoint> & verts,
                             std::vector<GLushort> & indices)
{
    // Open up the file
    MMFILE * f = MMfopen(path.c_str());
    if(f == NULL)
        return;

    // Loop through the entire file
    while(true) {
        // Read a line, yeah for C fixed buffer compensation (I hope)
        char buffer[500];
        string line;
        while(line.size() == 0 || line[line.size()-1] != '\n') {
            MMfgets(buffer, 500, f);
            if(buffer == NULL) {
                if(line.size() == 0) {
                    MMfclose(f);
                    return;
                } else
                    break;
            }
            line += buffer;
            if(line.size() == 0)
                break;
        }

        // Parse the wonderful thing:
        if(line.size() < 3)
            continue;
        if(line[0] == 'v' && line[1] == ' ') {

        } else if(line[0] == 'v' && line[1] == 'n' && line[2] == ' ') {

        } else if(line[0] == 'v' && line[1] == 't' && line[2] == ' ') {

        } else if(line[0] == 'f' && line[1] == ' ') {

        }
    }
}
