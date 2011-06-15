#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <pthread.h>s

#include "os_calls.h"
#include "glview.h"
#include "entity.h"
#include "sphere.h"
#include "plank.h"
#include "cannon.h"
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

    // marble buffers
    glBindBuffer(GL_ARRAY_BUFFER, buffers[MARBLE_BUF]);
    glBufferData(GL_ARRAY_BUFFER, Sphere::verts.size()*sizeof(DrawablePoint), &(Sphere::verts[0]), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[MARBLE_BUF + 1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Sphere::indices.size()*sizeof(GLushort), &(Sphere::indices[0]), GL_STATIC_DRAW);

    // Plank Buffers
    glBindBuffer(GL_ARRAY_BUFFER, buffers[PLANK_BUF]);
    glBufferData(GL_ARRAY_BUFFER, Plank::verts.size()*sizeof(DrawablePoint), &(Plank::verts[0]), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[PLANK_BUF + 1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Plank::indices.size()*sizeof(GLushort), &(Plank::indices[0]), GL_STATIC_DRAW);

    // Cannon buffers
    // TODO

    // Goal buffers
    // TODO

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

    // Draw all of the shapes in the gamestate
    for(PlankIterator i = state.planks.begin(); i != state.planks.end(); i++) {
        drawData(PLANK_BUF, *i);
    }
    for(CannonIterator i = state.cannons.begin(); i != state.cannons.end();
        i++) {
        i->draw();
    }
    state.goal.draw();
    drawData(MARBLE_BUF, state.marble);

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

void GLView::drawData(GLuint buffer, Drawable & d)
{
    // Get the indices for size later
    vector<GLushort> & indices = d.getIndices();

    // Assume the matrix and other data is correct
    // Matrix
    pthread_mutex_lock(&d.mvMatrixMutex);
    glUniformMatrix4fv(gvMVPHandle, 1, false, &(d.mvMatrix.matrix[0]));
    pthread_mutex_unlock(&d.mvMatrixMutex);
    // Vert data
    glBindBuffer(GL_ARRAY_BUFFER, buffers[buffer]);
    glEnableVertexAttribArray(gvPositionHandle);
    glVertexAttribPointer(gvPositionHandle, 3, GL_FLOAT, GL_FALSE, sizeof(DrawablePoint), 0);

    // Index data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[buffer + 1]);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, 0);
}
