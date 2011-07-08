#include <SDL/SDL.h>

#include "main.h"

// TODO: Make dynamic
#define WIDTH 640
#define HEIGHT 480

using namespace std;

static bool quit = false;

int main()
{
    // Set up SDL for opengl
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        fprintf(stderr, "Video initialization failed: %s\n", SDL_GetError());
        return 1;
    }
    const SDL_VideoInfo* info = SDL_GetVideoInfo();
    if (!info) {
        fprintf(stderr, "Video query failed: %s\n", SDL_GetError());
        return 1;
    }
    int w = WIDTH > 0 ? WIDTH : info->current_w;
    int h = HEIGHT > 0 ? HEIGHT : info->current_h;
    int bpp = info->vfmt->BitsPerPixel;

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    int flags = SDL_OPENGL | /*SDL_FULLSCREEN |*/ SDL_HWSURFACE | SDL_DOUBLEBUF;

    SDL_Surface * screen = SDL_SetVideoMode(w, h, bpp, flags);
    if (!screen) {
        fprintf(stderr, "Video mode set failed: %s\n", SDL_GetError());
        return 1;
    }

    // Set up opengl
    initGL();
    updateGL(w, h);

    // A few more things
    //SDL_WM_GrabInput(SDL_GRAB_ON);
    SDL_ShowCursor(SDL_DISABLE);

    // Set up and and start game running
    setupGame();
    startGame();

    SDL_Event event;

    // Main loop
    while(true) {
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                SDLKey & key = event.key.keysym.sym;
                if(key == SDLK_ESCAPE) {
                    quit = true;
                }
                break;
            }
        }

        if(quit) {
            pauseGame();
            stopGame();
            break;
        }
        draw();
        SDL_GL_SwapBuffers();
    }
    SDL_Quit();
    return 0;
}
