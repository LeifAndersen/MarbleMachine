#include <cstdio>
#include <cstdlib>

/**
  * The interface for OS dependant calls.
  * The actual implementation is in the OS dependand portion of the code.
  */
// Log calls
/**
  * Log an error accoring
  */
void log_e(const char * message)
{

}

/**
  * Log a warning, not fatel though
  */
void log_w(const char * message)
{

}

/**
  * log a message to the debug console
  */
void log_d(const char * message)
{

}

/**
  * Log a message to the vorbose console, or stdout
  */
void log_v(const char * message)
{

}

/**
  * Log a message to the info console
  */
void log_i(const char * message)
{

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

}

/**
  * Stops any music which is already playing.
  */
void stopMusic()
{

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
    return 0;
}

/**
  * Unloads a sound from memory.  Cannot call playSound on this ID until it's
  * loaded back into memory with loadSound.
  *
  * Input: soundID: the sound to be unloaded.
  */
void unloadSound(int soundID)
{

}

// File handles
// Directly maps to fopen/fclose/fchdir/etc.  Look at the man pages for docs.
typedef void MMFILE;
MMFILE * MMfopen(const char * path)
{
    return NULL;
}

void MMfclose(MMFILE * file)
{

}

void MMfchdir(const char * dir)
{

}

int MMfgetc(MMFILE * stream)
{
    return 0;
}

char * MMfgets(char * s, int size, MMFILE * stream)
{
    return NULL;
}

long MMfseek(MMFILE * stream, long offset, int type)
{

}

long MMftell(MMFILE * stream)
{
    return 0;
}

size_t MMfread(void * ptr, size_t size, size_t nmemb, MMFILE * stream)
{
    return 0;
}

int MMfeof(MMFILE * stream)
{
    return 0;
}

/**
  * Get the size of the file in bytes
  */
size_t MMfsize(MMFILE * stream)
{
    return 0;
}

// Time calls
typedef struct MMTIMER MMTIMER;

/**
  * Get a timer object
  */
MMTIMER * initTimer()
{
    return NULL;
}

/**
  * Destruct a timer object
  */
void deleteTimer(MMTIMER * timer)
{

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
    return 0;
}
