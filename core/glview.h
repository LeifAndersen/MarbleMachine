#ifndef GLVIEW_H
#define GLVIEW_H

#include <vector>

#include "include_opengl.h"
#include "game_state.h"
#include "drawable.h"

#define SHIP_BUF 0
#define PLANET_BUF 2
#define ANTI_PLANET_BUF 4
#define BUFS_NEEDED 6

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

    // Even Buffers for DrawablePoints
    // Odd Buffers for indices
    // Buffer 0: Marble
    GLuint buffers[BUFS_NEEDED];
    void drawData(GLuint buffer, Drawable & d, int indiceCount);
};

#endif // GLVIEW_H
