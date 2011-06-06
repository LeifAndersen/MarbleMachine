#include <android/log.h>

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

