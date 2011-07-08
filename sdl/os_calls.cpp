#include <cstdlib>
#include <cstdio>
#include <unistd.h>

#include <vector>
#include <string>

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

#include "os_calls.h"

using namespace std;

#define PREFIX "/usr/share/games"

/**
  * The interface for OS dependant calls.
  * The actual implementation is in the OS dependand portion of the code.
  */

// Calls specific to SDL
string getAssetsPath(string asset)
{
    string path;
#ifdef linux
    string home = getenv("HOME");
    path = home + "/gravity_well/data/";
#elif _WIN32
    path = GetModuleFileName(0);
#elif __APPLE__
#error Pleas do this for me.
#endif
    path += asset;
    return path;
}

// Log calls
/**
  * Log an error accoring
  */
void log_e(const char * message)
{
    puts(message);
}

/**
  * Log a warning, not fatel though
  */
void log_w(const char * message)
{
    puts(message);
}

/**
  * log a message to the debug console
  */
void log_d(const char * message)
{
    puts(message);
}

/**
  * Log a message to the vorbose console, or stdout
  */
void log_v(const char * message)
{
    puts(message);
}


/**
  * Log a message to the info console
  */
void log_i(const char * message)
{
    puts(message);
}

// Audio Calls

// Vector, SDL_mixer has it's own audio struct, we use ints
// So the int is an index into this vector.
vector<Mix_Chunk *> sound_chunks;
Mix_Music * music_data = NULL;

/**
  * Tells the operating system to start playing a sound file.
  * Should happen in another thread (this function should be farely quick).
  *
  * Multiple sounds can be played on top of each other.
  *
  * Input: soundID: The sound ID retrieved from the loadSound method
  *
  */
void playSound(int soundID)
{
    if(Mix_PlayChannel(-1, sound_chunks[soundID], 0) == -1) {
        fprintf(stderr, "Couldn't play sound: %d", soundID);
        //exit(1);
    }
}

/**
  * Tells the OS to play music.  Should happen in another thread.
  *
  * If music is already playing, it will stop it before starting.
  *
  * Input: music: A string to the music which needs to be played.
  *   file name, without the directory
  *
  */
void playMusic(const char * music)
{
    if(music_data)
        stopMusic();
    music_data = Mix_LoadMUS(getAssetsPath(music).c_str());
    if(!music_data) {
        fprintf(stderr, "Could not load music: %s", music);
        exit(1);
    }
    if(Mix_PlayMusic(music_data, -1) == -1) {
        fprintf(stderr, "Could not play music: %s", music);
    }
}

/**
  * Stops any music which is already playing.
  */
void stopMusic()
{
    if(!music_data)
        return;
    Mix_HaltMusic();
    Mix_FreeMusic(music_data);
}

/**
  * Loads a sound into memory for faster playing.  Must be called before
  * the playSound method on that sound. If the sound could not be loaded
  * for some reason, this method returns INT_MIN.
  *
  * Input: Sound: The sound to be loaded, without the directory.
  */
int loadSound(const char * sound)
{
    sound_chunks.push_back(Mix_LoadWAV(getAssetsPath(sound).c_str()));
    if(!sound_chunks[sound_chunks.size() - 1]) {
        fprintf(stderr, "Failed to load sound: %s", sound);
        exit(1);
    }
    return sound_chunks.size() - 1;
}

/**
  * Unloads a sound from memory.  Cannot call playSound on this ID until it's
  * loaded back into memory with loadSound.
  *
  * Input: soundID: the sound to be unloaded.
  */
void unloadSound(int soundID)
{
    Mix_FreeChunk(sound_chunks[soundID]);
}

// File handles
// Directly maps to fopen/fclose/fchdir/etc.  Look at the man pages for docs.
MMFILE * MMfopen(const char * path)
{
    return (MMFILE*) fopen(getAssetsPath(path).c_str(), "rb");
}

void MMfclose(MMFILE * file)
{
    fclose((FILE*)file);
}

void MMfchdir(const char * dir)
{
    chdir(dir);
}

int MMfgetc(MMFILE * stream)
{
    return fgetc((FILE*)stream);
}

char * MMfgets(char * s, int size, MMFILE * stream)
{
    return fgets(s, size, (FILE*)stream);
}

long MMfseek(MMFILE * stream, long offset, int type)
{
    return fseek((FILE*)stream, offset, type);
}

long MMftell(MMFILE * stream)
{
    return ftell((FILE*)stream);
}

size_t MMfread(void * ptr, size_t size, size_t nmemb, MMFILE * stream)
{
    return fread(ptr, size, nmemb, (FILE*)stream);
}

int MMfeof(MMFILE * stream)
{
    return feof((FILE*)stream);
}

/**
  * Get the size of the file in bytes
  */
size_t MMfsize(MMFILE * stream)
{
    return 0;
}

// Time calls
struct MMTIMER
{
    // For determining how much there is left to update
    // when time1older = true, replace time2,
    //      timeDelta will become time2-time1
    // otherwise replace time1,
    //      timedelta will become time1-time2
    long time1long;
    long time2long;
    long timeDelta;
    bool time1older;
};

/**
  * Get a timer object
  */
MMTIMER * initTimer()
{
    struct MMTIMER * timer = (struct MMTIMER *)malloc(sizeof(MMTIMER));

    timer->time2long = SDL_GetTicks()*1000000L;
    timer->time1older = true;
    return timer;
}

/**
  * Destruct a timer object
  */
void deleteTimer(MMTIMER * timer)
{
    free(timer);
}

/**
  * Get the time that has passed since the last time this time object was
  * passed in.
  *
  * For the first call, it will return the time difference since it
  * was created.
  *
  * Input: Time object that was used.
  * Output: Time that has passed, in nanoseconds
  */
long getTime(MMTIMER * timer)
{
    if(timer->time1older) {
        timer->time1long = SDL_GetTicks()*1000000L;
        timer->timeDelta = timer->time1long - timer->time2long;
        timer->time1older = false;
    } else {
        timer->time2long = SDL_GetTicks()*1000000L;
        timer->timeDelta = timer->time2long - timer->time1long;
        timer->time1older = true;
    }
    return timer->timeDelta;
}

/**
  * Get the current time
  */
time_t MMtime()
{
    return time_t();
}

// Texture calls

/**
  * Load a texture into memory.
  */
MMTEX * initTexture(const char * file)
{
    return (MMTEX *) SDL_LoadBMP(getAssetsPath(file).c_str());
}

/**
  * Free the texture.
  */
void deleteTexture(MMTEX * tex)
{
    SDL_FreeSurface((SDL_Surface *) tex);
}

/**
  * Get the data from the texture, in a form opengl can deal with
  */
void * getTexPixels(MMTEX * tex)
{
    return ((SDL_Surface *)tex)->pixels;
}

/**
  * Get the width of the texture.
  */
GLsizei getTexWidth(MMTEX * tex)
{
    return ((SDL_Surface *)tex)->w;
}

/**
  * Get the height of the texture.
  */
GLsizei getTexHeight(MMTEX * tex)
{
    return ((SDL_Surface *)tex)->h;
}

/**
  * Get the opengl format of the texture.
  */
GLint getTexFormat(MMTEX * tex)
{
    if(((SDL_Surface *)tex)->format->BytesPerPixel == 4)
        return GL_RGBA;
    else
        return GL_RGB;
}

/**
  * Is the texture compressed.
  * (The type of compression should be apparent with getformat).
  */
bool isTexCompressed(MMTEX * tex)
{
    return false;
}
