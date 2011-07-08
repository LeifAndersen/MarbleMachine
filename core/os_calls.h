#ifndef OS_CALLS_H
#define OS_CALLS_H

#include <cstdlib>
#include "include_opengl.h"

#define NO_DATA 0
#define LONG_DATA 1

/**
  * The interface for OS dependant calls.
  * The actual implementation is in the OS dependand portion of the code.
  */


// Log calls
/**
  * Log an error accoring
  */
void log_e(const char * message);

/**
  * Log a warning, not fatel though
  */
void log_w(const char * message);

/**
  * log a message to the debug console
  */
void log_d(const char * message);

/**
  * Log a message to the vorbose console, or stdout
  */
void log_v(const char * message);

/**
  * Log a message to the info console
  */
void log_i(const char * message);

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
void playSound(int soundID);

/**
  * Tells the OS to play music.  Should happen in another thread.
  *
  * If music is already playing, it will stop it before starting.
  *
  * Input: music: A string to the music which needs to be played.
  *   file name, without the directory
  *
  */
void playMusic(const char * music);

/**
  * Stops any music which is already playing.
  */
void stopMusic();

/**
  * Loads a sound into memory for faster playing.  Must be called before
  * the playSound method on that sound. If the sound could not be loaded
  * for some reason, this method returns INT_MIN.
  *
  * Input: Sound: The sound to be loaded, without the directory.
  */
int loadSound(const char * sound);

/**
  * Unloads a sound from memory.  Cannot call playSound on this ID until it's
  * loaded back into memory with loadSound.
  *
  * Input: soundID: the sound to be unloaded.
  */
void unloadSound(int soundID);

// File handles
// Directly maps to fopen/fclose/fchdir/etc.  Look at the man pages for docs.
// Only needs to be read only
typedef void MMFILE;
MMFILE * MMfopen(const char * path);
void MMfclose(MMFILE * file);
void MMfchdir(const char * dir);
int MMfgetc(MMFILE * stream);
char * MMfgets(char * s, int size, MMFILE * stream);
long MMfseek(MMFILE * stream, long offset, int type);
long MMftell(MMFILE * stream);
size_t MMfread(void * ptr, size_t size, size_t nmemb, MMFILE * stream);
int MMfeof(MMFILE * stream);

/**
  * Get the size of the file in bytes
  */
size_t MMfsize(MMFILE * stream);

// Data/Save calls
// Unlike file calls listed above, these are read/write, and used primarily
// for save state (where as the ones above are used mainly for asset loading).
// The API is designed to work like a dictionary, with KV pairs.

/**
  * Get the data associated with a key.
  *
  * Getting data that has not been saved is undefined.
  *
  * Input:  Key, the key for the data.
  *
  * Output: The data needed
  */
long getLongData(char * key);

/**
  * Test to see if data has already been saved for this key.
  *
  * Input: Key, for the data
  *
  * The type of data, currently either NO_DATA, or LONG_DATA
  */
unsigned int dataExists(char * key);

/**
  * Save the data as a long. Overwrite previous data if exists.
  *
  * Input:  key:  the data's key.
  *         data: The data to be stored.
  *
  * Output: If the data was succsefully stored.
  */
bool saveLongData(char * key, long data);

// Time calls
typedef struct MMTIMER MMTIMER;

/**
  * Get a timer object
  */
MMTIMER * initTimer();

/**
  * Destruct a timer object
  */
void deleteTimer(MMTIMER * timer);

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
long getTime(MMTIMER * timer);

/**
  * Get the current time
  */
time_t MMtime();

// Texture functions
typedef struct MMTEX MMTEX;

/**
  * Load a texture into memory.
  */
MMTEX * initTexture(const char * file);

/**
  * Free the texture.
  */
void deleteTexture(MMTEX * tex);

/**
  * Get the data from the texture, in a form opengl can deal with
  */
void * getTexPixels(MMTEX * tex);

/**
  * Get the width of the texture.
  */
GLsizei getTexWidth(MMTEX * tex);

/**
  * Get the height of the texture.
  */
GLsizei getTexHeight(MMTEX * tex);

/**
  * Get the opengl format of the texture.
  */
GLint getTexFormat(MMTEX * tex);

/**
  * Is the texture compressed.
  * (The type of compression should be apparent with getformat).
  */
bool isTexCompressed(MMTEX * tex);

#endif
