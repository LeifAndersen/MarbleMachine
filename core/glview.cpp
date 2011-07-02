#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <pthread.h>

#include "os_calls.h"
#include "glview.h"
#include "entity.h"
#include "sphere.h"
#include "goal.h"
#include "button.h"
#include "drawable.h"

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
    "precision mediump float;\n"
    "uniform sampler2D sTex;\n"
    "varying vec2 vTexCoord;\n"
    "varying vec4 vPrimaryColor;\n"
    "void main() {\n"
//    "  gl_FragColor = texture2d(sTex, vTexCoord)*vPrimaryColor;\n"
    "}\n";

GLView::GLView(GameState & state) : state(state)
{
}

bool GLView::initGL()
{
    // Load up shaders
    gProgram = createProgram(gVertexShader, gFragmentShader);
    if (!gProgram) {
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
    loadObjectBuff(SHIP_BUF, state.shipVerts, state.shipIndices);
    loadObjectBuff(PLANET_BUF, state.planetVerts, state.planetIndices);
    loadObjectBuff(ANTI_PLANET_BUF, state.antiPlanetVerts, state.antiPlanetIndices);

    // Texture buffers
    loadTextureBuffs(); // Currently does nothing
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(TEX_BUFS_NEEDED, texBuffers);
    glBindTexture(GL_TEXTURE_2D, texBuffers[SHIP_TEX_BUF]);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glCompressedTexImage2D(GL_TEXTURE_2D, 0, GL_ETC1_RGB8_OES, 1024, 1024, 0, GL_ETC1_RGB8_OES, &state.tex0[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Use etc compression
    // TODO: Perhaps use better compression later if needed

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

void GLView::loadTextureBuffs()
{
    // TODO
}

void GLView::renderFrame() {
    // Clear the screen
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    //drawData(GOAL_BUF, state.goal);
    drawData(SHIP_BUF, SHIP_TEX_BUF, state.ship, state.shipIndices.size());

    // Draw the planets (and anti-planets)
    pthread_mutex_lock(&state.planetsMutex);
    SphereIterator end = state.planets.end();
    for(SphereIterator i = state.planets.begin(); i != end; i++) {
        if(i->mass > 0)
            drawData(PLANET_BUF, PLANET_TEX_BUF, *i, state.planetIndices.size());
        else
            drawData(ANTI_PLANET_BUF, ANTI_PLANET_TEX_BUF, *i, state.antiPlanetIndices.size());
    }
    pthread_mutex_unlock(&state.planetsMutex);

    // TODO: Remove (currently kept as example code
    //glVertexAttrib4fv(gvColorHandle, gColor);
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
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texBuffers[texBuffer]);

    // Index data, and DRAW
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[buffer + 1]);
    glDrawElements(GL_TRIANGLES, indiceCount, GL_UNSIGNED_SHORT, 0);
}
