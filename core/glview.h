#ifndef GLVIEW_H
#define GLVIEW_H

#include "include_opengl.h"
#include "game_state.h"

class GLView
{
public:
    GLView(GameState & state);
    bool initGL();
    bool updateGL(int width, int height);
    void renderFrame();
private:
    GameState & state;
    GLuint createProgram(const char* pVertexSource, const char* pFragmentSource);
    GLuint loadShader(GLenum shaderType, const char* pSource);
    static const char gVertexShader[];

    static const char gFragmentShader[];

    GLuint gProgram;
    GLuint gvPositionHandle;
    GLuint gvColorHandle;
    GLuint gvMVPHandle;
};

#endif // GLVIEW_H
