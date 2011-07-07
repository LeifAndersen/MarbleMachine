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
    // Open up the proper level file
    char buff[500];
    snprintf(buff, 500, "level_%u", level);
    MMFILE * f = MMfopen(buff);
    if(!f) {
        exit(1);
        return;
    }

    // Clear out the level
    pthread_mutex_lock(&state.planetsMutex);
    state.planets.clear();
    pthread_mutex_unlock(&state.planetsMutex);

    // Ship's position;
    if(MMfread(&state.ship.position.x, 4, 1, f) != 1) {
        MMfclose(f);
        exit(1);
        return;
    }
    if(MMfread(&state.ship.position.y, 4, 1, f) != 1) {
        MMfclose(f);
        exit(1);
        return;
    }

    // Ship's velocity
    if(MMfread(&state.ship.velocity.x, 4, 1, f) != 1) {
        MMfclose(f);
        exit(1);
        return;
    }
    if(MMfread(&state.ship.velocity.y, 4, 1, f) != 1) {
        MMfclose(f);
        exit(1);
        return;
    }

    // Goal's position
    if(MMfread(&state.goal.position.x, 4, 1, f) != 1) {
        MMfclose(f);
        exit(1);
        return;
    }
    if(MMfread(&state.goal.position.y, 4, 1, f) != 1) {
        MMfclose(f);
        exit(1);
        return;
    }

    // Number of planets
    unsigned short planetCount;
    if(MMfread(&planetCount, 2, 1, f) != 1) {
        MMfclose(f);
        exit(1);
        return;
    }

    Sphere * planet;
    for(unsigned short i = 0; i < planetCount; i++)
    {
        state.planets.push_back(Sphere());
        planet = &state.planets.back();
        if(MMfread(&planet->position.x, 4, 1, f) != 1) {
            MMfclose(f);
            exit(1);
            return;
        }
        if(MMfread(&planet->position.y, 4, 1, f) != 1) {
            MMfclose(f);
            exit(1);
            return;
        }
        if(MMfread(&planet->velocity.x, 4, 1, f) != 1) {
            MMfclose(f);
            exit(1);
            return;
        }
        if(MMfread(&planet->velocity.y, 4, 1, f) != 1) {
            MMfclose(f);
            exit(1);
            return;
        }
        if(MMfread(&planet->mass, 4, 1, f) != 1) {
            MMfclose(f);
            exit(1);
        }
        if(MMfread(&planet->radius, 4, 1, f) != 1) {
            MMfclose(f);
            exit(1);
        }
    }

    // Close the level
    MMfclose(f);
}

void DataImporter::loadDrawables()
{
    parseData("marble.mp3", state.shipVerts, state.shipIndices);
    state.planetVerts = state.shipVerts;
    state.antiPlanetVerts = state.shipVerts;
    state.planetIndices = state.shipIndices;
    state.antiPlanetIndices = state.shipIndices;
}

void DataImporter::loadTextures()
{
    state.tex0 = initTexture("tex0_bmp.mp3");
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
