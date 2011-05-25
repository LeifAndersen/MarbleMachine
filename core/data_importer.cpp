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
    // First create the strings
    //objLoader loader;
    //string dataStr = getPath("marble");
    //char marbleStr[dataStr.size() + 1];
    //strncpy(marbleStr, dataStr.c_str(), dataStr.size() + 1);
    //dataStr = getPath("plank");
    //char plankStr[dataStr.size() + 1];
    //strncpy(plankStr, dataStr.c_str(), dataStr.size() + 1);
    //dataStr = getPath("cannon");
    //char cannonStr[dataStr.size() + 1];
    //strncpy(cannonStr, dataStr.c_str(), dataStr.size() + 1);
    //dataStr = getPath("goal");
    //char goalStr[dataStr.size() + 1];
    //strncpy(goalStr, dataStr.c_str(), dataStr.size() + 1);

    // Load up the marble data
    //loader.load(marbleStr);
    //cpyData(loader, Sphere::verts, Sphere::indices);

    // Load up the plank data
    //loader.load(plankStr);
    //cpyData(loader, Plank::verts, Plank::indices);

    // Load up the cannon data
    //loader.load(cannonStr);
    //cpyData(loader, Cannon::verts, Cannon::indices);

    // Load up the goal data
    //loader.load(goalStr);
    //cpyData(loader, Goal::verts, Goal::indices);

}
