#include <string>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#include "data_importer.h"

#include "game_state.h"
#include "os_calls.h"
#include "sphere.h"

using namespace std;

DataImporter::DataImporter(GameState & state) : state(state)
{
}

void DataImporter::loadLevel(unsigned int level)
{

}

void DataImporter::loadDrawables()
{
    parseData("/home/leif/MarbleMachine/assets/marble.mp3", state.shipVerts, state.shipIndices);
    state.planetVerts = state.shipVerts;
    state.antiPlanetVerts = state.shipVerts;
    state.planetIndices = state.shipIndices;
    state.antiPlanetIndices = state.shipIndices;
}

void DataImporter::loadTextures()
{
    parseTexData("tex0.mp3", state.tex0);
}

void DataImporter::parseData(const string & path,
                             std::vector<DrawablePoint> & verts,
                             std::vector<GLushort> & indices)
{
    // Open up the file
    MMFILE * f = MMfopen(path.c_str());
    if(f == NULL) {
        exit(1);
        return;
    }

    // Get the number of verts and faces.
    // Close file if not read properly.
    GLushort vertCount;
    if(MMfread(&vertCount, 2, 1, f) != 1) {
        MMfclose(f);
        exit(1);
        return;
    }
    GLushort indiceCount;
    if(MMfread(&indiceCount, 2, 1, f) != 1) {
        MMfclose(f);
        exit(1);
        return;
    }
    verts.reserve(vertCount);
    indices.reserve(indiceCount);

    // Load up all of the verts
    // Abort if error reading
    for(GLushort i = 0; i < vertCount; i++) {
        verts.push_back(DrawablePoint());
        if(MMfread(&verts[i], 4, 8, f) != 8) {
            MMfclose(f);
            exit(1);
            return;
        }
    }

    // Load up all of the indices
    // Abort if error reading
    for(GLushort i = 0; i < indiceCount; i++) {
        indices.push_back(0);
        if(MMfread(&indices[i], 2, 1, f) != 1) {
            MMfclose(f);
            exit(1);
            return;
        }
    }
    MMfclose(f);
    return;
}

void DataImporter::parseTexData(const std::string & path,
                                std::vector<DrawableColor> & pixels)
{
    MMFILE * f = MMfopen(path.c_str());
    if(f == NULL) {
        exit(1);
        return;
    }
    pixels.resize(1024 * 1024);
    if(MMfread(&pixels[0], 3, 1024 * 1024, f) != 1024*1024) {
        MMfclose(f);
        exit(1);
        return;
    }
}
