//
//  oscalls.cpp
//  MarbleMachine
//
//  Created by Nathan Swenson on 5/12/11.
//  Copyright 2011 Nathan Swenson. All rights reserved.
//

#include "os_calls.h"
#include <AudioToolbox/AudioToolbox.h>
#include <stdlib.h>
#include <stdio.h>
#include "MusicHandler.h"

// Returns the full path to a file in the iOS resources folder, given the filename.
// TODO: Make sure this actually works
NSString* fullPathToFile(const char * fileName)
{
    NSString* fileNameString = [NSString stringWithCString:fileName encoding:NSUTF8StringEncoding];
    NSString* resourcesPath = [[NSBundle mainBundle] bundlePath];
    NSString* filePath = [resourcesPath stringByAppendingPathComponent:fileNameString];
    return filePath;
}

// Log calls
/**
  * Log an error accoring
  * 
  *
  * Note: Not sure what all these different console message types are for. I just turned 'em all into NSLog calls.
  * - Nathan
 */

void log_e(const char * message)
{
    NSLog(@"Error: %s",message);
}

/**
  * Log a warning, not fatel though
  */
void log_w(const char * message)
{
    NSLog(@"Warning: %s",message);
}

/**
  * log a message to the debug console
  */
void log_d(const char * message)
{
    NSLog(@"Debug: %s",message);
}

/**
  * Log a message to the vorbose console, or stdout
  */
void log_v(const char * message)
{
    NSLog(@"Verbose: %s", message);
}

/**
  * Log a message to the info console
  */
void log_i(const char * message)
{
    NSLog(@"Info: %s", message);
}

// TODO: Maybe there's a problem casting between the sound id int and the uint32 SystemSoundID used by the iOS frameworks
// but it seems to work just fine.
void playSound(int soundID)
{
    AudioServicesPlaySystemSound((SystemSoundID)soundID);
}

int loadSound(const char * sound)
{
    NSString* objCSoundName = [NSString stringWithCString:sound encoding:NSUTF8StringEncoding];
    NSString* filePath = [[NSBundle mainBundle] pathForResource:objCSoundName ofType:@"wav"];
    
    // If something bad happens, make sure we return INT_MIN.
    if(filePath == nil)return INT_MIN;
    NSURL* filePathURL = [NSURL fileURLWithPath:filePath];
    
    // Probably just being paranoid here, but hey better safe than sorry.
    if(filePathURL == nil)return INT_MIN;
    
    // Just in case we have a successful file path but the sound doesn't load, initialize sysId with INT_MIN so we can return that.
    SystemSoundID sysId = INT_MIN;
    AudioServicesCreateSystemSoundID((CFURLRef)filePathURL, &sysId);
    return (int)sysId;
    
}

void unloadSound(int soundID)
{
    AudioServicesDisposeSystemSoundID((SystemSoundID)soundID);
}

void playMusic(const char * music)
{
    MusicHandler* handler = [MusicHandler sharedHandler];
    [handler playMusicNamed:[NSString stringWithCString:music encoding:NSUTF8StringEncoding]];
}

void stopMusic()
{
    MusicHandler* handler = [MusicHandler sharedHandler];
    [handler stopMusic];
}

// File handles
// Directly maps to fopen/fclose/fchdir/etc.  Look at the man pages for docs.
typedef void MMFILE;
MMFILE * MMfopen(const char * path)
{
    const char * fullPath = [fullPathToFile(path) cStringUsingEncoding:NSUTF8StringEncoding];
    return (MMFILE *)fopen(fullPath, "rb");
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
    // TODO: implement if this ever gets used.
    return NULL;
}

// Time calls
struct MMTIMER
{
    NSDate* dateSinceChecked;
};

/**
  * Get a timer object
  */
MMTIMER * initTimer()
{
    MMTIMER *timer = (MMTIMER*)malloc(sizeof(MMTIMER));
    NSDate* date = [[NSDate alloc] init];
    (*timer).dateSinceChecked = date;
    return timer;
}

/**
  * Destruct a timer object
  */
void deleteTimer(MMTIMER * timer)
{
    [timer -> dateSinceChecked release];
    delete timer;
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
    // Just a warning, there appears to be no NSAutoreleasePool in place for these os_calls. If you autorelease something here, it
    // will effectively be a memory leak. That's why I'm only using alloc+init and release. 
    
    // Find out how long its been since this timer was last accessed, and store that into a long (and convert to nanoseconds.)
    NSDate* previousDate = timer -> dateSinceChecked;
    NSDate* currentDate = [[NSDate alloc] init];
    long timeSincePreviousDate = (long)([currentDate timeIntervalSinceDate:previousDate] * 1000000000);
    
    // Delete the timer's previously stored date and replace it with the current date. Note: we are implicitly transferring
    // ownership of the currentDate object to the timer.
    [previousDate release];
    (*timer).dateSinceChecked = currentDate;
    
    // Return the time since timer was accessed.
    return timeSincePreviousDate;
}
