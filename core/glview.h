#ifndef GLVIEW_H
#define GLVIEW_H

#include "include_opengl.h"

class GLView
{
public:
    GLView();
    bool updateGL(int width, int height);
    void renderFrame();
private:
    GLuint createProgram(const char* pVertexSource, const char* pFragmentSource);
    GLuint loadShader(GLenum shaderType, const char* pSource);
    static const char gVertexShader[];

    static const char gFragmentShader[];

    GLuint gProgram;
    GLuint gvPositionHandle;

};

#endif // GLVIEW_H
