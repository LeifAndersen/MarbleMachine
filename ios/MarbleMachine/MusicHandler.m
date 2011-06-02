//
//  MusicHandler.m
//  MarbleMachine
//
//  Created by Nathan Swenson on 6/1/11.
//  Copyright 2011 Nathan Swenson. All rights reserved.
//

#import "MusicHandler.h"

#pragma mark -
#pragma mark Private Interface
@interface MusicHandler ()
- (void) initSingleton;
@end

#pragma mark -
#pragma mark Global Data
static MusicHandler* _Singleton = nil;

#pragma mark -
@implementation MusicHandler

#pragma mark Class Methods
+ (MusicHandler*) sharedHandler
{
    @synchronized(self) 
    {
        if (_Singleton == nil)
            [[self alloc] initSingleton];
    }
    
    return _Singleton;
}

+ (id) allocWithZone:(NSZone*)zone
{
    @synchronized(self) 
    {
        if (_Singleton == nil) 
        {
            _Singleton = [super allocWithZone:zone];
            return _Singleton;
        }
    }
    
    return nil;
}

#pragma mark -
#pragma mark Constructors
- (id) init
{
    NSAssert(false, @"Error: MusicHandler cannot be initialized with init method. Use [MusicHandler sharedHandler] instead.");
    return nil;
}

- (void) initSingleton
{
	_currentPlayer = nil;
}

- (id) copyWithZone:(NSZone*)zone
{
    return self;
}

- (void) dealloc
{
	[super dealloc];
}

#pragma mark -
#pragma mark Accessors

#pragma mark -
#pragma mark Methods
- (void) playMusicNamed:(NSString*)music
{
    if(_currentPlayer != nil)
    {
        [_currentPlayer stop];
        [_currentPlayer autorelease];
        _currentPlayer = nil;
    }
    NSString* musicPath = [[NSBundle mainBundle] pathForResource:music ofType:@"mp3"];
    if(musicPath == nil)
    {
        NSLog(@"Error loading music: No mp3 with name %@",music);
        return;
    }
    NSURL* musicPathURL = [NSURL fileURLWithPath:musicPath];
    NSError* error = nil;
    _currentPlayer = [[AVAudioPlayer alloc] initWithContentsOfURL:musicPathURL error:&error];
    if(error == nil)
    {
        [_currentPlayer play];
    }
    else
    {
        NSLog(@"Error loading music: %@",error);
        [_currentPlayer autorelease];
        _currentPlayer = nil;
    }
}

- (void) stopMusic
{
    if(_currentPlayer != nil)
    {
        [_currentPlayer stop];
        [_currentPlayer autorelease];
        _currentPlayer = nil;
    }
}

#pragma mark NSObject Methods
- (id) retain
{
    return self;
}

- (void) release
{
}
 
- (id) autorelease
{
    return self;
}

- (unsigned) retainCount
{
    return UINT_MAX;
}
 
@end
