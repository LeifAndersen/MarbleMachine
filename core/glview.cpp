#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "glview.h"
#include "entity.h"
#include "rotatable_entity.h"
#include "sphere.h"
#include "plank.h"
#include "cannon.h"
#include "goal.h"
#include "button.h"
#include "drawable.h"

// TODO: REMOVE ME
const GLfloat gTriangleVertices[] = { 0.0f, 0.5f, -0.5f, -0.5f,
        0.5f, -0.5f };

const char GLView::gVertexShader[] =
    "attribute vec4 vPosition;\n"
    "void main() {\n"
    "  gl_Position = vPosition;\n"
    "}\n";

const char GLView::gFragmentShader[] =
    "precision mediump float;\n"
    "void main() {\n"
    "  gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);\n"
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
    gvPositionHandle = glGetAttribLocation(gProgram, "vPosition");

    glClearColor(0, 0, 0, 0);

    // Load up vertex and texture data
    Entity::loadData();
    RotatableEntity::loadData();
    Drawable::loadData();
    Sphere::loadData();
    Plank::loadData();
    Cannon::loadData();
    Goal::loadData();
    Button::loadData();

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
    // Clear the screen, and start shader
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glUseProgram(gProgram);

    // Draw all of the shapes in the gamestate
    for(PlankIterator i = state.planks.begin(); i != state.planks.end(); i++) {
        i->draw();
    }
    for(CannonIterator i = state.cannons.begin(); i != state.cannons.end();
        i++) {
        i->draw();
    }
    state.goal.draw();
    state.marble.draw();

    // TODO: Remove (currently kept as example code
    glVertexAttribPointer(gvPositionHandle, 2, GL_FLOAT, GL_FALSE, 0, gTriangleVertices);
    glEnableVertexAttribArray(gvPositionHandle);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
