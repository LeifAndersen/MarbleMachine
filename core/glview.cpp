#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <pthread.h>

#include "os_calls.h"
#include "glview.h"
#include "entity.h"
#include "sphere.h"
#include "button.h"
#include "drawable.h"
#include "include_opengl.h"

using namespace std;

const char GLView::gVertexShader[] =
    "uniform mat4 uMVP;\n"
    "attribute vec4 aPosition;\n"
    "attribute vec4 aNormal;\n"
    "attribute vec2 aTexCoord;\n"
    "varying vec2 vTexCoord;\n"
    "varying vec4 vPrimaryColor;\n"
    "void main() {\n"
    "  gl_Position = uMVP * aPosition;\n"
    "  vPrimaryColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
    "  vTexCoord = aTexCoord;\n"
    "}\n";

const char GLView::gFragmentShader[] =
#ifdef __GLES__
    "precision mediump float;\n"
#endif
    "uniform sampler2D sTex;\n"
    "varying vec2 vTexCoord;\n"
    "varying vec4 vPrimaryColor;\n"
    "void main() {\n"
    "  gl_FragColor = texture2D(sTex, vTexCoord)*vPrimaryColor;\n"
    "}\n";

GLView::GLView(GameState & state) : state(state)
{
}

bool GLView::initGL()
{
    // Load up shaders
    gProgram = createProgram(gVertexShader, gFragmentShader);
    if (!gProgram) {
        exit(1);
        return false;
    }

    // Get attributes
    gvPositionHandle = glGetAttribLocation(gProgram, "aPosition");
    gvNormalHandle = glGetAttribLocation(gProgram, "aNormal");
    gvTexCoordHandle = glGetAttribLocation(gProgram, "aTexCoord");

    // Get uniforms
    gvMVPHandle = glGetUniformLocation(gProgram, "uMVP");

    // Get textures
    gsTexHandle = glGetUniformLocation(gProgram, "sTex");

    // Set the clear color
    glClearColor(0, 0, 0, 0);

    // Load up vertex and texture data
    // Prepare an opengl buffer for the data,
    // assume that data has already been loaded

    // Bind buffers
    glGenBuffers(BUFS_NEEDED, buffers);

    // Load buffers
    // Object buffers
    loadObjectBuff(SHIP_BUF, state.shipVerts, state.shipIndices);
    loadObjectBuff(LIGHT_PLANET_BUF, state.lightPlanetVerts, state.lightPlanetIndices);
    loadObjectBuff(MEDIUM_PLANET_BUF, state.mediumPlanetVerts, state.mediumPlanetIndices);
    loadObjectBuff(HEAVY_PLANET_BUF, state.heavyPlanetVerts, state.heavyPlanetIndices);
    loadObjectBuff(ANTI_PLANET_BUF, state.antiPlanetVerts, state.antiPlanetIndices);
    loadObjectBuff(BLACK_HOLE_BUF, state.blackHoleVerts, state.blackHoleIndices);
    loadObjectBuff(GOAL_BUF, state.goalVerts, state.goalIndices);
    loadObjectBuff(ACTIVE_PLANET_BUF, state.activePlanetVerts, state.activePlanetIndices);
    loadButtonBuff(MENU_BUTTON_BUF, state.menuButton);
    loadButtonBuff(MUTE_EFX_BUTTON_BUF, state.muteEfxButton);
    loadButtonBuff(UNMUTE_EFX_BUTTON_BUF, state.unMuteEfxButton);
    loadButtonBuff(MUTE_MUSIC_BUTTON_BUF, state.muteMusicButton);
    loadButtonBuff(LIGHT_PLANET_BUTTON_BUF, state.lightPlanetButton);
    loadButtonBuff(MEDIUM_PLANET_BUTTON_BUF, state.mediumPlanetButton);
    loadButtonBuff(HEAVY_PLANET_BUTTON_BUF, state.heavyPlanetButton);
    loadButtonBuff(ANTI_PLANET_BUTTON_BUF, state.antiPlanetButton);
    loadButtonBuff(RESTART_LEVEL_BUTTON_BUF, state.restartLevelButton);
    loadButtonBuff(QUIT_LEVEL_BUTTON_BUF, state.quitLevelButton);
    loadButtonBuff(WON_LEVEL_BUTTON_BUF, state.wonLevelButton);
    loadButtonBuff(COUNTER_BUTTON_BUF, state.counter);
    loadButtonBuff(LOST_LEVEL_BUTTON_BUF, state.lostLevelButton);
    loadBackgroundBuff(BACKGROUND_BUF, state.background);

    // Texture buffers
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(TEX_BUFS_NEEDED, texBuffers);
    glBindTexture(GL_TEXTURE_2D, texBuffers[SHIP_TEX_BUF]);
    if(isTexCompressed(state.tex0)) {
        glCompressedTexImage2D(GL_TEXTURE_2D, 0, getTexFormat(state.tex0),
                               getTexWidth(state.tex0),
                               getTexHeight(state.tex0), 0,
                               8 * ((getTexWidth(state.tex0) + 3) >> 2)
                                 * ((getTexHeight(state.tex0) + 3) >> 2),
                               getTexPixels(state.tex0));
    } else {
        glTexImage2D(GL_TEXTURE_2D, 0, getTexFormat(state.tex0),
                     getTexWidth(state.tex0), getTexHeight(state.tex0), 0,
                     getTexFormat(state.tex0), GL_UNSIGNED_BYTE,
                     getTexPixels(state.tex0));
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Start up a buffer:
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texBuffers[SHIP_TEX_BUF]);
    activeTexBuffer = texBuffers[SHIP_TEX_BUF];

    // Start up the program
    glUseProgram(gProgram);
    return true;
}

bool GLView::updateGL(int width, int height)
{
    // Set the viewport
    glViewport(0, 0, width, height);
    return true;
}

GLuint GLView::createProgram(const char* pVertexSource, const char* pFragmentSource)
{
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, pVertexSource);
    if (!vertexShader) {
        return 0;
    }

    GLuint pixelShader = loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
    if (!pixelShader) {
        return 0;
    }

    GLuint program = glCreateProgram();
    if (program) {
        glAttachShader(program, vertexShader);
        glAttachShader(program, pixelShader);
        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE) {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength) {
                char* buf = (char*) malloc(bufLength);
                if (buf) {
                    glGetProgramInfoLog(program, bufLength, NULL, buf);
                    free(buf);
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}

GLuint GLView::loadShader(GLenum shaderType, const char* pSource) {
    GLuint shader = glCreateShader(shaderType);
    if (shader) {
        glShaderSource(shader, 1, &pSource, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen) {
                char* buf = (char*) malloc(infoLen);
                if (buf) {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    free(buf);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
}

void GLView::loadObjectBuff(GLuint buffer, std::vector<DrawablePoint> & verts,
                            std::vector<GLushort> & indices)
{
    glBindBuffer(GL_ARRAY_BUFFER, buffers[buffer]);
    glBufferData(GL_ARRAY_BUFFER, verts.size()*sizeof(DrawablePoint),
                 &(verts[0]), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[buffer + 1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(GLushort),
                 &(indices[0]), GL_STATIC_DRAW);
}

void GLView::loadButtonBuff(GLuint buffer, const Button &button)
{
    glBindBuffer(GL_ARRAY_BUFFER, buffers[buffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(button_verts_t)*BUTTON_STATES,
                 &button.texCoords, GL_STATIC_DRAW);
}

void GLView::loadBackgroundBuff(GLuint buffer,
                                const button_verts_t &background)
{
    glBindBuffer(GL_ARRAY_BUFFER, buffers[buffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(button_verts_t),
                 &background, GL_STATIC_DRAW);
}

void GLView::renderFrame()
{
    // Load data if needed
    pthread_mutex_lock(&state.dataLoadingMutex);
    if(state.dataNeedsLoading) {
        loadBackgroundBuff(BACKGROUND_BUF, state.background);
    }
    state.dataNeedsLoading = false;
    pthread_mutex_unlock(&state.dataLoadingMutex);

    // Clear the screen
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    // Draw the background
    drawBackground(BACKGROUND_BUF, BACKGROUND_TEX_BUF);

    // Planets (state specific)
    SphereIterator end = state.planets.end();
    unsigned int j = 1;
    pthread_mutex_lock(&state.modeMutex);
    switch(state.mode) {
    case MODE_GALACTIC_MENU:
        pthread_mutex_unlock(&state.modeMutex);

        // Draw the targets
        j = 1;
        pthread_mutex_lock(&state.planetsMutex);
        for(SphereIterator i = state.planets.begin();
            i != end && j <= state.highestSector; i++, j++) {
            drawData(GOAL_BUF, GOAL_TEX_BUF, *i, state.goalIndices.size());
        }
        pthread_mutex_unlock(&state.planetsMutex);
        break;
    case MODE_GALACTIC_SECTOR_MENU:
        pthread_mutex_unlock(&state.modeMutex);

        // Draw the targets
        pthread_mutex_lock(&state.planetsMutex);
        if(state.sector >= state.highestSector) {
            j = 1;
            for(SphereIterator i = state.planets.begin();
                i != end && j <= state.highestLevel; i++, j++) {
                drawData(GOAL_BUF, GOAL_TEX_BUF, *i, state.goalIndices.size());
            }
        } else {
            for(SphereIterator i = state.planets.begin(); i != end; i++) {
                drawData(GOAL_BUF, GOAL_TEX_BUF, *i, state.goalIndices.size());
            }
        }
        pthread_mutex_unlock(&state.planetsMutex);
        break;
    case MODE_LEVEL:
    case MODE_LEVEL_WON:
    case MODE_LEVEL_LOST:
        pthread_mutex_unlock(&state.modeMutex);

        // Draw the buttons on screen
        drawButton(LIGHT_PLANET_BUTTON_BUF, LIGHT_PLANET_BUTTON_TEX_BUF,
                   state.lightPlanetButton);
        drawCountersOnButton(COUNTER_BUTTON_BUF, COUNTER_BUTTON_TEX_BUF, state.lightPlanets,
                             state.counter, state.lightPlanetButton);
        drawButton(MEDIUM_PLANET_BUTTON_BUF, MEDIUM_PLANET_BUTTON_TEX_BUF,
                   state.mediumPlanetButton);
        drawCountersOnButton(COUNTER_BUTTON_BUF, COUNTER_BUTTON_TEX_BUF, state.mediumPlanets,
                             state.counter, state.mediumPlanetButton);
        drawButton(HEAVY_PLANET_BUTTON_BUF, HEAVY_PLANET_BUTTON_TEX_BUF,
                   state.heavyPlanetButton);
        drawCountersOnButton(COUNTER_BUTTON_BUF, COUNTER_BUTTON_TEX_BUF, state.heavyPlanets,
                             state.counter, state.heavyPlanetButton);
        drawButton(ANTI_PLANET_BUTTON_BUF, ANTI_PLANET_BUTTON_TEX_BUF,
                   state.antiPlanetButton);
        drawCountersOnButton(COUNTER_BUTTON_BUF, COUNTER_BUTTON_TEX_BUF, state.antiPlanets,
                             state.counter, state.antiPlanetButton);

        // Draw the ship and goal
        drawData(GOAL_BUF, GOAL_TEX_BUF, state.goal, state.goalIndices.size());
        drawData(SHIP_BUF, SHIP_TEX_BUF, state.ship, state.shipIndices.size());

        // Draw the 'active planet', if one is one the screen.
        if(state.activePlanetInUse) {
            drawData(ACTIVE_PLANET_BUF, ACTIVE_PLANET_TEX_BUF, state.activePlanet,
                     state.activePlanetIndices.size());
        }

        // Draw the planets (and anti-planets)
        pthread_mutex_lock(&state.planetsMutex);
        for(SphereIterator i = state.planets.begin(); i != end; i++) {
            if(i->mass < 0)
                drawData(ANTI_PLANET_BUF, ANTI_PLANET_TEX_BUF, *i, state.antiPlanetIndices.size());
            else if(i->mass < LIGHT_PLANET_WEIGHT_MAX)
                drawData(LIGHT_PLANET_BUF, LIGHT_PLANET_TEX_BUF, *i, state.lightPlanetIndices.size());
            else if(i->mass < MEDIUM_PLANET_WEIGHT_MAX)
                drawData(MEDIUM_PLANET_BUF, MEDIUM_PLANET_TEX_BUF, *i, state.mediumPlanetIndices.size());
            else if(i->mass < HEAVY_PLANET_WEIGHT_MAX)
                drawData(HEAVY_PLANET_BUF, HEAVY_PLANET_TEX_BUF, *i, state.heavyPlanetIndices.size());
            else
                drawData(BLACK_HOLE_BUF, BLACK_HOLE_TEX_BUF, *i, state.blackHoleIndices.size());
        }
        pthread_mutex_unlock(&state.planetsMutex);

        // Buttons
        if(state.wonLevelButton.buttonOnScreen) {
            drawButton(WON_LEVEL_BUTTON_BUF, WON_LEVEL_BUTTON_TEX_BUF, state.wonLevelButton);
        }
        if(state.lostLevelButton.buttonOnScreen) {
           drawButton(LOST_LEVEL_BUTTON_BUF, LOST_LEVEL_BUTTON_TEX_BUF, state.lostLevelButton);
        }
        break;
    default:
        pthread_mutex_unlock(&state.modeMutex);
        break;
    }

    // Buttons
    drawButton(MENU_BUTTON_BUF, MENU_BUTTON_TEX_BUF, state.menuButton);
    if(state.menuOn) {
        if(state.efxMuted) {
            drawButton(UNMUTE_EFX_BUTTON_BUF, UNMUTE_EFX_BUTTON_TEX_BUF, state.unMuteEfxButton);
        } else {
            drawButton(MUTE_EFX_BUTTON_BUF, MUTE_EFX_BUTTON_TEX_BUF, state.muteEfxButton);
        }
        if(state.musicMuted) {
            drawButton(UNMUTE_MUSIC_BUTTON_BUF, UNMUTE_EFX_BUTTON_TEX_BUF, state.unMuteEfxButton);
        } else {
            drawButton(MUTE_MUSIC_BUTTON_BUF, MUTE_MUSIC_BUTTON_TEX_BUF, state.muteMusicButton);
        }
        drawButton(QUIT_LEVEL_BUTTON_BUF, QUIT_LEVEL_BUTTON_TEX_BUF, state.quitLevelButton);
        drawButton(RESTART_LEVEL_BUTTON_BUF, RESTART_LEVEL_BUTTON_TEX_BUF, state.restartLevelButton);
    }
}

void GLView::drawData(GLuint buffer, GLuint texBuffer,
                      Drawable & drawable,int indiceCount)
{
    //Hack
    DrawablePoint * nulldraw = NULL;

    // Set up the matrix
    drawable.loadMVMatrix();
    drawable.mvMatrix.matrix = (drawable.mvMatrix*state.projectionMatrix).matrix;

    // Assume the matrix and other data is correct
    // Matrix
    glUniformMatrix4fv(gvMVPHandle, 1, false, &(drawable.mvMatrix.matrix[0]));

    // Vert data
    glBindBuffer(GL_ARRAY_BUFFER, buffers[buffer]);
    glEnableVertexAttribArray(gvPositionHandle);
    glVertexAttribPointer(gvPositionHandle, 3, GL_FLOAT, GL_FALSE,
                          sizeof(DrawablePoint), &nulldraw->x);

    // Normal data
    glEnableVertexAttribArray(gvNormalHandle);
    glVertexAttribPointer(gvNormalHandle, 3, GL_FLOAT, GL_FALSE,
                          sizeof(DrawablePoint), &nulldraw->nx);

    // texcoord data
    glEnableVertexAttribArray(gvTexCoordHandle);
    glVertexAttribPointer(gvTexCoordHandle, 2, GL_FLOAT, GL_FALSE,
                          sizeof(DrawablePoint), &nulldraw->u);

    // Make sure correct texure is loaded
    if(texBuffers[texBuffer] != activeTexBuffer) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texBuffers[texBuffer]);
        activeTexBuffer = texBuffers[activeTexBuffer];
    }
    // Index data, and DRAW
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[buffer + 1]);
    glDrawElements(GL_TRIANGLES, indiceCount, GL_UNSIGNED_SHORT, 0);
}

void GLView::drawButton(GLuint buffer, GLuint texBuffer,
                Button & button)
{
    //Hack to get the write button
    DrawablePoint * nulldraw = NULL;

    // Set up the matrix
    button.loadMVMatrix();
    button.mvMatrix.matrix = (button.mvMatrix*state.projectionMatrix).matrix;

    // Assume the matrix and other data is correct
    // Matrix
    glUniformMatrix4fv(gvMVPHandle, 1, false, &(button.mvMatrix.matrix[0]));

    // Vert data
    glBindBuffer(GL_ARRAY_BUFFER, buffers[buffer]);
    glEnableVertexAttribArray(gvPositionHandle);
    glVertexAttribPointer(gvPositionHandle, 3, GL_FLOAT, GL_FALSE,
                          sizeof(DrawablePoint), &nulldraw->x);

    // Normal data
    glEnableVertexAttribArray(gvNormalHandle);
    glVertexAttribPointer(gvNormalHandle, 3, GL_FLOAT, GL_FALSE,
                          sizeof(DrawablePoint), &nulldraw->nx);

    // texcoord data
    glEnableVertexAttribArray(gvTexCoordHandle);
    glVertexAttribPointer(gvTexCoordHandle, 2, GL_FLOAT, GL_FALSE,
                          sizeof(DrawablePoint), &nulldraw->u);

    // Make sure correct texure is loaded
    if(texBuffers[texBuffer] != activeTexBuffer) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texBuffers[texBuffer]);
        activeTexBuffer = texBuffers[activeTexBuffer];
    }

    // Index data, and DRAW
    // glDrawElements(GL_TRIANGLE_STRIP, indiceCount, GL_UNSIGNED_SHORT, 0);
    glDrawArrays(GL_TRIANGLE_FAN, button.state, 4);
}

void GLView::drawBackground(GLuint buffer, GLuint texBuffer)
{
    //Hack to get the write button
    DrawablePoint * nulldraw = NULL;

    // Set up the matrix
    Matrix m;
    m.loadIdentity();
    m.scale(WIDTH, WIDTH, WIDTH);
    m.matrix = (m*state.projectionMatrix).matrix;

    // Assume the matrix and other data is correct
    // Matrix
    glUniformMatrix4fv(gvMVPHandle, 1, false, &m.matrix[0]);

    // Vert data
    glBindBuffer(GL_ARRAY_BUFFER, buffers[buffer]);
    glEnableVertexAttribArray(gvPositionHandle);
    glVertexAttribPointer(gvPositionHandle, 3, GL_FLOAT, GL_FALSE,
                          sizeof(DrawablePoint), &nulldraw->x);

    // Normal data
    glEnableVertexAttribArray(gvNormalHandle);
    glVertexAttribPointer(gvNormalHandle, 3, GL_FLOAT, GL_FALSE,
                          sizeof(DrawablePoint), &nulldraw->nx);

    // texcoord data
    glEnableVertexAttribArray(gvTexCoordHandle);
    glVertexAttribPointer(gvTexCoordHandle, 2, GL_FLOAT, GL_FALSE,
                          sizeof(DrawablePoint), &nulldraw->u);

    // Make sure correct texure is loaded
    if(texBuffers[texBuffer] != activeTexBuffer) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texBuffers[texBuffer]);
        activeTexBuffer = texBuffers[activeTexBuffer];
    }

    // Index data, and DRAW
    // glDrawElements(GL_TRIANGLE_STRIP, indiceCount, GL_UNSIGNED_SHORT, 0);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void GLView::drawCountersOnButton(GLuint buffer, GLuint texBuffer,
                                  unsigned short ammount, Button &counter,
                                  Button &button)
{
    // Determin how wide it can be made
    unsigned short maxWidth = (unsigned short)floorf(button.widthHalf/counter.widthHalf);
    unsigned short maxHeight = (unsigned short)floorf(button.heightHalf/counter.heightHalf);

    // Set the inital positino
    counter.x = button.x - button.widthHalf + counter.widthHalf;
    counter.y = button.y + button.heightHalf - counter.heightHalf;

    // iterate
    unsigned short drawn = 0;
    for(unsigned short i = 0; i < maxHeight && drawn < ammount;
        i++, counter.x = button.x - button.widthHalf + counter.widthHalf,
        counter.y -= counter.heightHalf*2.0f) {
        for(unsigned short j = 0; j < maxWidth && drawn < ammount;
            j++, drawn++, counter.x += counter.widthHalf*2.0f) {
            drawButton(buffer, texBuffer, counter);
        }
    }
}

void GLView::drawDataNoVBO(std::vector<DrawablePoint> &verts,
                           std::vector<GLushort> &indices, GLuint texBuffer, Drawable &drawable)
{
    // Set up the matrix
    drawable.loadMVMatrix();
    drawable.mvMatrix.matrix = (drawable.mvMatrix*state.projectionMatrix).matrix;

    // Assume the matrix and other data is correct
    // Matrix
    glUniformMatrix4fv(gvMVPHandle, 1, false, &(drawable.mvMatrix.matrix[0]));

    // Vert data
    glEnableVertexAttribArray(gvPositionHandle);
    glVertexAttribPointer(gvPositionHandle, 3, GL_FLOAT, GL_FALSE,
                          sizeof(DrawablePoint), &verts[0].x);

    // Normal data
    glEnableVertexAttribArray(gvNormalHandle);
    glVertexAttribPointer(gvNormalHandle, 3, GL_FLOAT, GL_FALSE,
                          sizeof(DrawablePoint), &verts[0].nx);

    // texcoord data
    glEnableVertexAttribArray(gvTexCoordHandle);
    glVertexAttribPointer(gvTexCoordHandle, 2, GL_FLOAT, GL_FALSE,
                          sizeof(DrawablePoint), &verts[0].u);

    // Make sure correct texure is loaded
    if(texBuffers[texBuffer] != activeTexBuffer) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texBuffers[texBuffer]);
        activeTexBuffer = texBuffers[activeTexBuffer];
    }
    // Index data, and DRAW
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, &indices[0]);
}

void GLView::drawButtonNoVBO(GLuint texBuffer, Button &button)
{
    // Set up the matrix
    button.loadMVMatrix();
    button.mvMatrix.matrix = (button.mvMatrix*state.projectionMatrix).matrix;

    // Assume the matrix and other data is correct
    // Matrix
    glUniformMatrix4fv(gvMVPHandle, 1, false, &(button.mvMatrix.matrix[0]));

    // Vert data
    glEnableVertexAttribArray(gvPositionHandle);
    glVertexAttribPointer(gvPositionHandle, 3, GL_FLOAT, GL_FALSE,
                          sizeof(DrawablePoint), &button.texCoords[0].corners[0].x);

    // Normal data
    glEnableVertexAttribArray(gvNormalHandle);
    glVertexAttribPointer(gvNormalHandle, 3, GL_FLOAT, GL_FALSE,
                          sizeof(DrawablePoint), &button.texCoords[0].corners[0].nx);

    // texcoord data
    glEnableVertexAttribArray(gvTexCoordHandle);
    glVertexAttribPointer(gvTexCoordHandle, 2, GL_FLOAT, GL_FALSE,
                          sizeof(DrawablePoint), &button.texCoords[0].corners[0].u);

    // Make sure correct texure is loaded
    if(texBuffers[texBuffer] != activeTexBuffer) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texBuffers[texBuffer]);
        activeTexBuffer = texBuffers[activeTexBuffer];
    }

    // Index data, and DRAW
    glDrawArrays(GL_TRIANGLE_FAN, button.state, 4);
}
