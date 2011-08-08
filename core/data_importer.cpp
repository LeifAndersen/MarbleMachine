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

void DataImporter::loadGalaxy()
{
    MMFILE * f = MMfopen("galaxy.mp3");
    if(!f) {
        log_e("Couldn't open up main galaxy.");
        exit(1);
    }

    if(MMfread(&state.background, sizeof(button_verts_t), 1, f) != 1) {
        MMfclose(f);
        log_e("Couldn't read main galaxy.");
        exit(1);
    }

    state.planets.clear();

    unsigned short sectorCount;
    if(MMfread(&sectorCount, sizeof(unsigned short), 1, f) != 1) {
        MMfclose(f);
        log_e("Couldn't read main galaxy.");
        exit(1);
    }
    for(unsigned int i = 0; i < sectorCount; i++) {
        vec3_t data;
        state.planets.push_back(Sphere());
        Sphere & planet = state.planets.back();
        if(MMfread(&data, sizeof(vec3_t), 1, f) != 1) {
            MMfclose(f);
            log_e("Couldn't read main galaxy.");
            exit(1);
        }
        planet.position.x = data.x;
        planet.position.y = data.y;
        planet.position.z = 0.0f;
        planet.radius = data.z;
    }
    MMfclose(f);

    state.sectorsInGalaxy = state.planets.size();
}

void DataImporter::loadSector(unsigned int sector)
{
    char buff[500];
    snprintf(buff, 500, "sector_%u.mp3", sector);
    MMFILE * f = MMfopen(buff);
    if(!f) {
        log_e("Failed to find sector");
        exit(1);
        return;
    }


    if(MMfread(&state.background, sizeof(button_verts_t), 1, f) != 1) {
        MMfclose(f);
        log_e("Couldn't properly load zone");
        exit(1);
    }

    unsigned short levelCount;
    if(MMfread(&levelCount, sizeof(unsigned short), 1, f) != 1) {
        MMfclose(f);
        log_e("Couldn't find level count");
        exit(1);
    }

    state.planets.clear();
    for(unsigned int i = 0; i < levelCount; i++) {
        state.planets.push_back(Sphere());
        Sphere & level = state.planets.back();

        vec3_t data;
        if(MMfread(&data, sizeof(vec3_t), 1, f) != 1) {
            MMfclose(f);
            log_e("Couldn't read level.");
            exit(1);
        }
        level.position.x = data.x;
        level.position.y = data.y;
        level.position.z = 0.0f;
        level.radius = data.z;
    }

    MMfclose(f);

    state.levelsInSector = state.planets.size();
}

void DataImporter::loadLevel(unsigned int sector, unsigned int level)
{
    // Open up the proper level file
    char buff[500];
    snprintf(buff, 500, "level_%u_%u.mp3", sector, level);
    MMFILE * f = MMfopen(buff);
    if(!f) {
        log_e("Couldn't open level");
        exit(1);
        return;
    }

    // Clear out the level
    pthread_mutex_lock(&state.planetsMutex);
    state.planets.clear();
    pthread_mutex_unlock(&state.planetsMutex);

    // Ship's position nad velocity
    float data[6];
    if(MMfread(&data[0], sizeof(float), 6, f) != 6) {
        MMfclose(f);
        log_e("Couldn't read level");
        exit(1);
        return;
    }

    state.ship.position.x = data[0];
    state.ship.position.y = data[1];
    state.ship.velocity.x = data[2];
    state.ship.velocity.y = data[3];
    state.ship.mass = data[4];
    state.ship.radius = data[5];

    // Goal's position
    if(MMfread(&data[0], sizeof(float), 6, f) != 6) {
        MMfclose(f);
        exit(1);
        return;
    }

    state.goal.position.x = data[0];
    state.goal.position.y = data[1];
    state.goal.velocity.x = data[2];
    state.goal.velocity.y = data[3];
    state.goal.mass = data[4];
    state.goal.radius = data[5];

    unsigned short planetData[4];
    if(MMfread(&planetData[0], sizeof(unsigned short), 4, f) != 4) {
        MMfclose(f);
        log_e("Couldn't read player resources for level");
        exit(1);
        return;
    }

    state.lightPlanets = planetData[0];
    state.mediumPlanets = planetData[1];
    state.heavyPlanets = planetData[2];
    state.antiPlanets = planetData[3];

    // Number of planets
    unsigned short planetCount;
    if(MMfread(&planetCount, sizeof(unsigned short), 1, f) != 1) {
        MMfclose(f);
        exit(1);
        return;
    }

    Sphere * planet;
    for(unsigned short i = 0; i < planetCount; i++)
    {
        state.planets.push_back(Sphere());
        planet = &state.planets.back();
        if(MMfread(&data[0], sizeof(float), 6, f) != 6) {
            MMfclose(f);
            exit(1);
            return;
        }

        planet->position.x = data[0];
        planet->position.y = data[1];
        planet->velocity.x = data[2];
        planet->velocity.y = data[3];
        planet->mass = data[4];
        planet->radius = data[5];
    }

    // Close the level
    MMfclose(f);
}

void DataImporter::loadDrawables()
{
    // First the entities
    parseData("ship.mp3", state.shipVerts, state.shipIndices);
    parseData("light_planet.mp3", state.lightPlanetVerts, state.lightPlanetIndices);
    parseData("medium_planet.mp3", state.mediumPlanetVerts, state.mediumPlanetIndices);
    parseData("heavy_planet.mp3", state.heavyPlanetVerts, state.heavyPlanetIndices);
    parseData("anti_planet.mp3", state.antiPlanetVerts, state.antiPlanetIndices);
    parseData("goal.mp3", state.goalVerts, state.goalIndices);
    parseData("active_planet.mp3", state.activePlanetVerts, state.activePlanetIndices);
    // Next the buttons
    loadButton("menu.button.mp3", state.menuButton);
    loadButton("restart.button.mp3", state.restartLevelButton);
    loadButton("light_planet.button.mp3", state.lightPlanetButton);
    loadButton("medium_planet.button.mp3", state.mediumPlanetButton);
    loadButton("heavy_planet.button.mp3", state.heavyPlanetButton);
    loadButton("anti_planet.button.mp3", state.heavyPlanetButton);
    loadButton("won_level.button.mp3", state.wonLevelButton);

    // Final, tye fonts
    MMFILE * f = MMfopen("font.mp3");
    if(!f) {
        log_e("Could not open font.mp3");
        exit(1);
    }
    if(MMfread(state.font_chars, sizeof(button_verts_t), FONT_CHAR_SIZE, f) != FONT_CHAR_SIZE) {
        log_e("Could not read all font characters");
        exit(1);
    }
    MMfclose(f);
}

void DataImporter::loadTextures()
{
    state.tex0 = initTexture("tex0.mp3");
}

void DataImporter::saveGame()
{
    // Back up current save (if exists)
    // TODO

    // Save Game
    FILE * f = fopen(getSavePath("save").c_str(), "wb");
    if(!f) {
        log_e("Couldn't save game");
        return;
    }

    // Save version (so it can be changed in a newer version if needed).
    unsigned int saveVersion = 0;
    if(fwrite(&saveVersion, sizeof(unsigned int), 1, f) != 1) {
        log_e("Couldn't save data");
        fclose(f);
        return;
    }

    // Save what level player is on
    pthread_mutex_lock(&state.miscMutex);
    if(fwrite(&state.highestSector, sizeof(unsigned int), 1, f) != 1) {
        pthread_mutex_unlock(&state.miscMutex);
        log_e("Couldn't save game progress");
        fclose(f);
        return;
    }
    if(fwrite(&state.highestLevel, sizeof(unsigned int), 1, f) != 1) {
        pthread_mutex_unlock(&state.miscMutex);
        log_e("Couldn't save game progress");
        fclose(f);
        return;
    }
    if(fflush(f)) {
        pthread_mutex_unlock(&state.miscMutex);
        log_e("Couldn't save game progress");
        fclose(f);
        return;
    }
    pthread_mutex_unlock(&state.miscMutex);

    // Close file
    if(fclose(f)) {
        log_e("Couldn't save game progress");
        return;
    }
}

void DataImporter::loadGame()
{
    FILE * f = fopen(getSavePath("save").c_str(), "rb");
    if(!f) {
        log_v("Couldn't open data for loading, loading new game");
        loadDefaultGame();
        return;
    }

    unsigned int saveVersion;
    if(fread(&saveVersion, sizeof(unsigned int), 1, f) != 1) {
        log_e("Couldn't read game data, making new game");
        loadDefaultGame();
        return;
    }

    // Load what level the player is on
    pthread_mutex_lock(&state.miscMutex);
    if(fread(&state.highestSector, sizeof(unsigned int), 1, f) != 1) {
        pthread_mutex_unlock(&state.modeMutex);
        log_e("Couldn't read game data, making new game");
        loadDefaultGame();
        return;
    }
    if(fread(&state.highestLevel, sizeof(unsigned int), 1, f) != 1) {
        pthread_mutex_unlock(&state.modeMutex);
        log_e("Couldn't read game data, making new game");
        loadDefaultGame();;
        return;
    }
    pthread_mutex_unlock(&state.miscMutex);

    fclose(f);
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
    unsigned short vertCount;
    if(MMfread(&vertCount, sizeof(unsigned short), 1, f) != 1) {
        MMfclose(f);
        exit(1);
        return;
    }
    unsigned short indiceCount;
    if(MMfread(&indiceCount, sizeof(unsigned short), 1, f) != 1) {
        MMfclose(f);
        exit(1);
        return;
    }
    verts.reserve(vertCount);
    indices.reserve(indiceCount);

    // Load up all of the verts
    // Abort if error reading
    for(unsigned short i = 0; i < vertCount; i++) {
        verts.push_back(DrawablePoint());
        if(MMfread(&verts[i], sizeof(DrawablePoint), 1, f) != 1) {
            MMfclose(f);
            exit(1);
            return;
        }
    }

    // Load up all of the indices
    // Abort if error reading
    for(unsigned short i = 0; i < indiceCount; i++) {
        indices.push_back(0);
        if(MMfread(&indices[i], sizeof(GLushort), 1, f) != 1) {
            MMfclose(f);
            exit(1);
            return;
        }
    }
    MMfclose(f);
    return;
}

void DataImporter::loadButton(const std::string &path, Button &button)
{
    MMFILE * f = MMfopen(path.c_str());
    if(!f) {
        log_e("Could not open button.");
        exit(1);
        return;
    }
    if(MMfread(&button.texCoords[0], sizeof(button_verts_t), BUTTON_STATES, f) != BUTTON_STATES) {
        log_e("Could not read all button data.");
        exit(1);
        return;
    }
    MMfclose(f);
}

void DataImporter::loadDefaultGame()
{
    pthread_mutex_lock(&state.modeMutex);
    state.mode = MODE_GALACTIC_MENU_SETUP;
    pthread_mutex_unlock(&state.modeMutex);
    pthread_mutex_lock(&state.miscMutex);
    state.highestLevel = 1;
    state.highestSector = 1;
    pthread_mutex_unlock(&state.miscMutex);
    pthread_mutex_lock(&state.planetsMutex);
    state.planets.clear();
    pthread_mutex_unlock(&state.planetsMutex);
}
