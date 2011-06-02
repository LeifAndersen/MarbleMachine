//
//  MusicHandler.h
//  MarbleMachine
//
//  Created by Nathan Swenson on 6/1/11.
//  Copyright 2011 Nathan Swenson. All rights reserved.
//

#import <AVFoundation/AVAudioPlayer.h>

@interface MusicHandler : NSObject 
{
    AVAudioPlayer* _currentPlayer;
}

// Stops any music currently playing, and starts new music with the given filename. Note: filename should be provided without an
// extension, as the file type is assumed to be mp3. If this is not the case, change this method to be more robust. :P
- (void) playMusicNamed:(NSString*)music;

- (void) stopMusic;

// This is how you should always get a reference to a MusicHandler object, because it is meant to be shared.
+ (MusicHandler*) sharedHandler;

@end
