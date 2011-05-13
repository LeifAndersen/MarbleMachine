//
//  oscalls.cpp
//  MarbleMachine
//
//  Created by Nathan Swenson on 5/12/11.
//  Copyright 2011 Nathan Swenson. All rights reserved.
//

#include "os_calls.h"
#include <AudioToolbox/AudioToolbox.h>

// TODO: Maybe there's a problem casting between the sound id int and the uint32 SystemSoundID used by the iOS frameworks
void playSound(int soundID)
{
    AudioServicesPlaySystemSound((SystemSoundID)soundID);
}

int loadSound(std::string sound)
{
    char const * cSoundName = sound.c_str();
    NSString* objCSoundName = [NSString stringWithCString:cSoundName encoding:NSUTF8StringEncoding];
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