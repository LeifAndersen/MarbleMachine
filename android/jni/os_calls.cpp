#include <android/log.h>
#include <ctime>
#include <cstdlib>
#include <vector>

#include "nv_sound.h"
#include "nv_file.h"
#include "os_calls.h"

// Log calls
/**
  * Log an error accoring
  */
void log_e(const char * message)
{
    __android_log_print(ANDROID_LOG_ERROR, "MarbleMachine", message);
}

/**
  * Log a warning, not fatel though
  */
void log_w(const char * message)
{
    __android_log_print(ANDROID_LOG_WARN, "MarbleMachine", message);
}

/**
  * log a message to the debug console
  */
void log_d(const char * message)
{
    __android_log_print(ANDROID_LOG_DEBUG, "MarbleMachine", message);
}

/**
  * Log a message to the vorbose console, or stdout
  */
void log_v(const char * message)
{
    __android_log_print(ANDROID_LOG_VERBOSE, "MarbleMachine", message);
}

/**
  * Log a message to the info console
  */
void log_i(const char * message)
{
    __android_log_print(ANDROID_LOG_INFO, "MarbleMachine", message);
}

// Audio Calls
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
    SoundPoolPlaySound(soundID, 1.0f, 1.0f, 1, 0, 1.0f);
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
    MediaPlayerSetDataSource(music);
}

/**
  * Stops any music which is already playing.
  */
void stopMusic()
{
    MediaPlayerStop();
}

/**
  * Loads a sound into memory for faster playing.  Must be called before
  * the playSound method on that sound.
  *
  * Inpupt: Sound: The sound to be loaded, without the directory.
  */
int loadSound(const char * sound)
{
    return SoundPoolLoadSFX(sound, 1);
}

/**
  * Unloads a sound from memory.  Cannot call playSound on this ID until it's
  * loaded back into memory with loadSound.
  *
  * Input: soundID: the sound to be unloaded.
  */
void unloadSound(int soundID)
{
    SoundPoolUnloadSample(soundID);
}

// File handles
// Directly maps to fopen/fclose/fchdir/etc.  Look at the man pages for docs.
MMFILE * MMfopen(const char * path)
{
    return (MMFILE*) NvFOpen(path);
}

void MMfclose(MMFILE * file)
{
    NvFClose((NvFile*)file);
}

void MMfchdir(const char * dir)
{
    NvFChdir(dir);
}

int MMfgetc(MMFILE * stream)
{
    return NvFGetc((NvFile*)stream);
}

char * MMfgets(char * s, int size, MMFILE * stream)
{
    return NvFGets(s, size, (NvFile*)stream);
}

long MMfseek(MMFILE * stream, long offset, int type)
{
    return NvFSeek((NvFile*)stream, offset, type);
}

long MMftell(MMFILE * stream)
{
    return NvFTell((NvFile*)stream);
}

size_t MMfread(void * ptr, size_t size, size_t nmemb, MMFILE * stream)
{
    return NvFRead(ptr, size, nmemb, (NvFile*)stream);
}

int MMfeof(MMFILE * stream)
{
    return NvFEOF((NvFile*)stream);
}

/**
  * Get the size of the file in bytes
  */
size_t MMfsize(MMFILE * stream)
{
    return NvFSize((NvFile*)stream);
}

// Time calls
struct MMTIMER
{
    // For determining how much there is left to update
    // when time1older = true, replace time2,
    //      timeDelta will become time2-time1
    // otherwise replace time1,
    //      timedelta will become time1-time2
    struct timespec time1;
    long time1long;
    struct timespec time2;
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

    clock_gettime(CLOCK_MONOTONIC, &timer->time2);
    timer->time2long = (long)timer->time2.tv_sec*1000000000LL + timer->time2.tv_nsec;
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
        clock_gettime(CLOCK_MONOTONIC, &timer->time1);
        timer->time1long = (long)timer->time1.tv_sec*1000000000LL + timer->time1.tv_nsec;
        timer->timeDelta = timer->time1long - timer->time2long;
        timer->time1older = false;
    } else {
        clock_gettime(CLOCK_MONOTONIC, &timer->time2);
        timer->time2long = (long)timer->time2.tv_sec*1000000000LL + timer->time2.tv_nsec;
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

struct MMTEX {
    std::vector<GLushort> pixels;
    size_t pixelCount;
};

// Texture functions
/**
  * Load a texture into memory.
  */
MMTEX * initTexture(const char * file)
{
    MMTEX * tex = (MMTEX *)malloc(sizeof(MMTEX));
    MMFILE * f = MMfopen(file);
    if(f == NULL) {
        exit(1);
    }

    tex->pixels.reserve(1024*1024*3);
    //tex->pixelCount = /..
    MMfread(&tex->pixels[0], 1, 1024*1024*3, f);
    tex->pixelCount = 8 * ((1024 + 3) >> 2) * ((1024 + 3) >> 2);
    MMfclose(f);
    return tex;
}

/**
  * Free the texture.
  */
void deleteTexture(MMTEX * tex)
{
    free(tex);
}

/**
  * Get the data from the texture, in a form opengl can deal with
  */
void * getTexPixels(MMTEX * tex)
{
    return &tex->pixels[0];
}

/**
  * Get the width of the texture.
  */
GLsizei getTexWidth(MMTEX * tex)
{
    return 1024;
}

/**
  * Get the height of the texture.
  */
GLsizei getTexHeight(MMTEX * tex)
{
    return 1024;
}

/**
  * Get the opengl format of the texture.
  */
GLint getTexFormat(MMTEX * tex)
{
    return GL_ETC1_RGB8_OES;
}

/**
  * Is the texture compressed.
  * (The type of compression should be apparent with getformat).
  */
bool isTexCompressed(MMTEX * tex)
{
    return true;
}
