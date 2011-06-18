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
    parseData("marble.mp3", Sphere::verts, Sphere::indices);
}

void DataImporter::parseData(string path, std::vector<DrawablePoint> & verts,
                             std::vector<GLushort> & indices)
{
    // Open up the file
    MMFILE * f = MMfopen(path.c_str());
    if(f == NULL)
        return;

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
        if(MMfread(&verts[i].x, 4, 1, f) != 1) {
            MMfclose(f);
            exit(1);
            return;
        }
        if(MMfread(&verts[i].y, 4, 1, f) != 1) {
            MMfclose(f);
            exit(1);
            return;
        }
        if(MMfread(&verts[i].z, 4, 1, f) != 1) {
            MMfclose(f);
            exit(1);
            return;
        }
        if(MMfread(&verts[i].nx, 4, 1, f) != 1) {
            MMfclose(f);
            exit(1);
            return;
        }
        if(MMfread(&verts[i].ny, 4, 1, f) != 1) {
            MMfclose(f);
            exit(1);
            return;
        }
        if(MMfread(&verts[i].nz, 4, 1, f) != 1) {
            MMfclose(f);
            exit(1);
            return;
        }
        if(MMfread(&verts[i].u, 4, 1, f) != 1) {
            MMfclose(f);
            exit(1);
            return;
        }
        if(MMfread(&verts[i].v, 4, 1, f) != 1) {
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
