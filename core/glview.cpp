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
    "attribute vec4 aColor;\n"
    "attribute vec2 aTexCoord;\n"
    "varying vec4 vColor;\n"
    "void main() {\n"
    "  gl_Position = uMVP * aPosition;\n"
    "  vColor = aColor;\n"
    "}\n";

const char GLView::gFragmentShader[] =
    "precision mediump float;\n"
    "varying vec4 vColor;\n"
    "void main() {\n"
//    "  gl_FragColor = vColor;\n"
    "  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
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
    gvColorHandle = glGetAttribLocation(gProgram, "aColor");

    // Get uniforms
    gvMVPHandle = glGetUniformLocation(gProgram, "uMVP");

    // Set the clear color
    glClearColor(0, 0, 0, 0);

    // Load up vertex and texture data
    // Prepare an opengl buffer for the data,
    // assume that data has already been loaded

    // Bind buffers
    glGenBuffers(BUFS_NEEDED, buffers);

    // ship buffers
    glBindBuffer(GL_ARRAY_BUFFER, buffers[SHIP_BUF]);
    glBufferData(GL_ARRAY_BUFFER, state.shipVerts.size()*sizeof(DrawablePoint), &(state.shipVerts[0]), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[SHIP_BUF + 1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, state.shipIndices.size()*sizeof(GLushort), &(state.shipIndices[0]), GL_STATIC_DRAW);

    // Planet buffers
    glBindBuffer(GL_ARRAY_BUFFER, buffers[PLANET_BUF]);
    glBufferData(GL_ARRAY_BUFFER, state.planetVerts.size()*sizeof(DrawablePoint), &(state.planetVerts[0]), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[PLANET_BUF + 1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, state.planetIndices.size()*sizeof(GLushort), &(state.planetIndices[0]), GL_STATIC_DRAW);

    // Antiplanet buffers
    glBindBuffer(GL_ARRAY_BUFFER, buffers[ANTI_PLANET_BUF]);
    glBufferData(GL_ARRAY_BUFFER, state.antiPlanetVerts.size()*sizeof(DrawablePoint), &(state.antiPlanetVerts[0]), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[PLANET_BUF + 1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, state.antiPlanetIndices.size()*sizeof(GLushort), &(state.antiPlanetIndices[0]), GL_STATIC_DRAW);

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

GLuint GLView::createProgram(const char* pVertexSource, const char* pFragmentSource) {
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


void GLView::renderFrame() {
    // Clear the screen
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    //drawData(GOAL_BUF, state.goal);
    drawData(SHIP_BUF, state.ship, state.shipIndices.size());

    // Draw the planets (and anti-planets)
    pthread_mutex_lock(&state.planetsMutex);
    SphereIterator end = state.planets.end();
    for(SphereIterator i = state.planets.begin(); i != end; i++) {
        if(i->mass > 0)
            drawData(PLANET_BUF, *i, state.planetIndices.size());
        else
            drawData(ANTI_PLANET_BUF, *i, state.antiPlanetIndices.size());
    }
    pthread_mutex_unlock(&state.planetsMutex);

    // TODO: Remove (currently kept as example code
    //glEnableVertexAttribArray(gvPositionHandle);
    //glVertexAttribPointer(gvPositionHandle, 2, GL_FLOAT, GL_FALSE, 0, gTriangleVertices);
    //glVertexAttrib4fv(gvColorHandle, gColor);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    //glVertexAttribPointer(gvPositionHandle, 2, GL_FLOAT, GL_FALSE, 0, gTriangleVertices2);
    //glVertexAttribPointer(gvColorHandle, 4, GL_FLOAT, GL_FALSE, 0, gColor2);
    //glVertexAttrib4fv(gvColorHandle, gColor2);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
}

void GLView::drawData(GLuint buffer, Drawable d, int indiceCount)
{
    // Set up the matrix
    d.loadMVMatrix();
    d.mvMatrix.matrix = (d.mvMatrix*state.projectionMatrix).matrix;

    // Assume the matrix and other data is correct
    // Matrix
    glUniformMatrix4fv(gvMVPHandle, 1, false, &(d.mvMatrix.matrix[0]));

    // Vert data
    glBindBuffer(GL_ARRAY_BUFFER, buffers[buffer]);
    glEnableVertexAttribArray(gvPositionHandle);
    glVertexAttribPointer(gvPositionHandle, 3, GL_FLOAT, GL_FALSE, sizeof(DrawablePoint), 0);

    // Index data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[buffer + 1]);
    glDrawElements(GL_TRIANGLES, indiceCount, GL_UNSIGNED_SHORT, 0);
}
