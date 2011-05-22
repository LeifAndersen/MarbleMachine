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

const char GLView::gVertexShader[] =
    "attribute vec4 aPosition;\n"
    "attribute vec4 aNormal;\n"
    "attribute vec4 aColor;\n"
    "attribute vec2 aTexCoord;\n"
    "varying vec4 vColor;\n"
    "void main() {\n"
    "  gl_Position = aPosition;\n"
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

    // Set the clear color
    glClearColor(0, 0, 0, 0);

    // Load up vertex and texture data
    Entity::loadData();
    RotatableEntity::loadData();
    Drawable::loadData();
    Sphere::loadData(gvPositionHandle);
    Plank::loadData();
    Cannon::loadData();
    Goal::loadData();
    Button::loadData();

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
        //glBindAttribLocation(program, 0, "aPosition");
        //glBindAttribLocation(program, 1, "aColor");
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
        i->draw();
    }
    for(CannonIterator i = state.cannons.begin(); i != state.cannons.end();
        i++) {
        i->draw();
    }
    state.goal.draw();
    state.marble.draw();

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
