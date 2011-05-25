#include "nv_sound.h"
#include "os_calls.h"

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
void playMusic(std::string music)
{
    MediaPlayerSetDataSource(music.c_str());
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
int loadSound(std::string sound)
{
    return SoundPoolLoadSFX(sound.c_str(), 1);
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

/**
  * Return the full string for a path given the proper
  * file name.
  *
  * Input: The file name
  * Output: The full path, intluding the file,
  * for file opening.
  */
std::string getPath(std::string filename)
{
    return "/mnt/sdcard/test-data/" + filename;
}
