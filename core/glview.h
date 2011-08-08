#ifndef GLVIEW_H
#define GLVIEW_H

#include <vector>

#include "include_opengl.h"
#include "game_state.h"
#include "drawable.h"

// Buffers
#define BUFS_NEEDED 29
#define TEX_BUFS_NEEDED 1

// Regular buffers
#define SHIP_BUF 0
#define LIGHT_PLANET_BUF 2
#define MEDIUM_PLANET_BUF 4
#define HEAVY_PLANET_BUF 6
#define BLACK_HOLE_BUF 8
#define ANTI_PLANET_BUF 10
#define ACTIVE_PLANET_BUF 12
#define GOAL_BUF 14

// Background buffer
#define BACKGROUND_BUF 16

// Button Buffer
#define MENU_BUTTON_BUF 17
#define MUTE_EFX_BUTTON_BUF 18
#define UNMUTE_EFX_BUTTON_BUF 19
#define MUTE_MUSIC_BUTTON_BUF 20
#define UNMUTE_MUSIC_BUTTON_BUF 21
#define LIGHT_PLANET_BUTTON_BUF 22
#define MEDIUM_PLANET_BUTTON_BUF 23
#define HEAVY_PLANET_BUTTON_BUF 24
#define ANTI_PLANET_BUTTON_BUF 25
#define RESTART_LEVEL_BUTTON_BUF 26
#define QUIT_LEVEL_BUTTON_BUF 27
#define WON_LEVEL_BUTTON_BUF 28

// Texture buffers
#define BACKGROUND_TEX_BUF 0
#define SHIP_TEX_BUF 0
#define LIGHT_PLANET_TEX_BUF 0
#define MEDIUM_PLANET_TEX_BUF 0
#define HEAVY_PLANET_TEX_BUF 0
#define BLACK_HOLE_TEX_BUF 0
#define ANTI_PLANET_TEX_BUF 0
#define ACTIVE_PLANET_TEX_BUF 0
#define GOAL_TEX_BUF 0
#define MENU_BUTTON_TEX_BUF 0
#define MUTE_EFX_BUTTON_TEX_BUF 0
#define UNMUTE_EFX_BUTTON_TEX_BUF 0
#define MUTE_MUSIC_BUTTON_TEX_BUF 0
#define UNMUTE_MUSIC_BUTTON_TEX_BUF 0
#define LIGHT_PLANET_BUTTON_TEX_BUF 0
#define MEDIUM_PLANET_BUTTON_TEX_BUF 0
#define HEAVY_PLANET_BUTTON_TEX_BUF 0
#define ANTI_PLANET_BUTTON_TEX_BUF 0
#define RESTART_LEVEL_BUTTON_TEX_BUF 0
#define QUIT_LEVEL_BUTTON_TEX_BUF 0
#define WON_LEVEL_BUTTON_TEX_BUF 0

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
      * Load all of the buffers for the class
      *
      * Input: buffer:  The input buffer.
      *        button:  The button containing the data to be loaded.
      */
    void loadButtonBuff(GLuint buffer, const Button & button);

    /**
      *
      */
    void loadBackgroundBuff(GLuint buffer, const button_verts_t & background);

    /**
      * Draw data onto the screen associated with the buffer.
      *
      * Input buffer:      Index into buffers[] where the data is.
      *       texbuffer:   Index into texbuffers[] where the data is
      *       drawable:    A drawable, for the few things not loaded
      *                        into a vbuffer.
      *       indiceCount: The number of indicies in the buffer to be drawn.
      */
    void drawData(GLuint buffer, GLuint texBuffer,
                  Drawable & drawable, int indiceCount);

    /**
      * Draw a button onto a screen.
      *
      * Input: buffer:    The buffer index to the location of verts to use.
      *        texbuffer: The buffer index to the location of
      *                       the texture to use.
      *        button:    The button to be drawn.
      */
    void drawButton(GLuint buffer, GLuint texBuffer,
                    Button & button);

    /**
      *
      */
    void drawBackground(GLuint buffer, GLuint texBuffer);

    /**
      * Draw data onto the screen associated with the buffer.
      *
      * Input verts:       The verts to draw
      *       indices:     The indices to draw
      *       texbuffer:   Index into texbuffers[] where the data is
      *       drawable:    A drawable, for the few things not loaded
      *                        into a vbuffer.
      *       indiceCount: The number of indicies in the buffer to be drawn.
      */
    void drawDataNoVBO(std::vector<DrawablePoint> & verts,
                       std::vector<GLushort> & indices, GLuint texBuffer,
                       Drawable & drawable);

    /**
      * Draw a button onto a screen.
      *
      * Input:
      *        texbuffer: The buffer index to the location of
      *                       the texture to use.
      *        button:    The button to be drawn.
      */
    void drawButtonNoVBO(GLuint texBuffer, Button & button);
};

#endif // GLVIEW_H
