#ifndef GLVIEW_H
#define GLVIEW_H

#include <vector>

#include "include_opengl.h"
#include "game_state.h"
#include "drawable.h"

#define SHIP_BUF 0
#define LIGHT_PLANET_BUF 2
#define MEDIUM_PLANET_BUF 4
#define HEAVY_PLANET_BUF 6
#define BLACK_HOLE_BUF 8
#define ANTI_PLANET_BUF 10
#define BUFS_NEEDED 12

#define SHIP_TEX_BUF 0
#define LIGHT_PLANET_TEX_BUF 0
#define MEDIUM_PLANET_TEX_BUF 0
#define HEAVY_PLANET_TEX_BUF 0
#define BLACK_HOLE_TEX_BUF 0
#define ANTI_PLANET_TEX_BUF 0
#define TEX_BUFS_NEEDED 1

class GLView
{
public:
    /**
      * Constructs the GLView.
      *
      * Once called the view is not necisarily ready to draw, initGL and
      * updateGL must first be called.
      *
      * Input: state: The game state so the glview knows what to draw.
      *
      */
    GLView(GameState & state);

    /**
      * Called once the program has started.  Sets up all of the buffers and
      * whatnot for opengl to run.
      *
      * Assumes that an opengl context has already been created though. (As it
      * is platform dependant).
      *
      */
    bool initGL();

    /**
      * Called whenever the viewport changes.  Updates all of the need openGL
      * stuff to safely change it.
      *
      * Input: width:  the width of the viewport.
      *        height: the height of the viewport.
      *
      */
    bool updateGL(int width, int height);

    /**
      * Called whenever the game wants opengl to draw to the screen.
      * Assumes that both initGL and updateGL have already been called.
      */
    void renderFrame();
private:
    GameState & state;

    static const char gVertexShader[];

    static const char gFragmentShader[];

    GLuint gProgram;
    GLuint gvPositionHandle;
    GLuint gvNormalHandle;
    GLuint gvTexCoordHandle;
    GLuint gvMVPHandle;
    GLuint gsTexHandle;

    // Even Buffers for DrawablePoints
    // Odd Buffers for indices
    // Buffer 0: Marble
    GLuint buffers[BUFS_NEEDED];

    // Texture buffers
    GLuint texBuffers[TEX_BUFS_NEEDED];
    GLuint activeTexBuffer;

    /**
      * Create a programm using the given shader (to be called in initGL)
      *
      * Input: char* to the two proper shaders.
      */
    GLuint createProgram(const char* pVertexSource, const char* pFragmentSource);

    /**
      * Loads a shader into openGL. (To be called by createProgram)
      *
      * Input: shaderType: The type of shader desired (vertex/fragment)
      *        pSource:    A char* to the shader to be loaded.
      */
    GLuint loadShader(GLenum shaderType, const char* pSource);

    /**
      * Load all of the buffers for the objects in the class.
      *
      * Objects meaning vertex data, index data, etc.
      *
      * Input: buffer:  Index to buffers for the data buffers
      *        verts:   A list of the verts for the object
      *        indices: A list of the indices for the verts
      */
    void loadObjectBuff(GLuint buffer, std::vector<DrawablePoint> & verts,
                        std::vector<GLushort> & indices);

    /**
      * Load up the textures needed
      */
    void loadTextureBuffs();

    /**
      * Draw data onto the screen associated with the buffer.
      *
      * Input buffer:      Index into buffers[] where the data is.
      *       drawable:    A drawable, for the few things not loaded
      *                        into a vbuffer.
      *       indiceCount: The number of indicies in the buffer to be drawn.
      */
    void drawData(GLuint buffer, GLuint texBuffer,
                  Drawable & drawable, int indiceCount);
};

#endif // GLVIEW_H
