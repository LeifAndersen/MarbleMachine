//
//  MarbleMachineAppDelegate.m
//  MarbleMachine
//
//  Created by Nathan Swenson on 5/9/11.
//  Copyright 2011 Nathan Swenson. All rights reserved.
//

#import "MarbleMachineAppDelegate.h"
#import "EAGLView.h"
#import "main.h"


@implementation MarbleMachineAppDelegate

#pragma mark UIApplicationDelegate Methods
- (void) applicationDidFinishLaunching:(UIApplication*)application 
{
    // Create window and OpenGL view
	_window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
	_glView = [[EAGLView alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
	[_window addSubview:_glView];
	[_window makeKeyAndVisible];
    init([_glView renderbufferWidth], [_glView renderbufferHeight]);
    
    // Sets up the draw loop to be run at intervals.
    [NSTimer scheduledTimerWithTimeInterval:1.0f/30.0f target:self selector:@selector(drawGame) userInfo:nil repeats:YES];
    
    // Initialize some needed variables
    _currentSoundID = 0;
    _currentSoundName = [@"" retain];
}

- (void) applicationWillTerminate:(UIApplication*)application 
{
	[_window release];
	[_glView release];
}

- (void) applicationWillResignActive:(UIApplication*)application
{
}

- (void) applicationDidEnterBackground:(UIApplication*)application
{
}

- (void) applicationWillEnterForeground:(UIApplication*)application
{
}

- (void) applicationDidBecomeActive:(UIApplication*)application
{
}


#pragma mark Methods

- (void) drawGame
{
    [_glView startDraw];
    draw();
    [_glView commitDraw];
}

// This method checks the "getSound" method of the C++ code to see if it should be playing any audio file.
/*
- (void) doSound
{
    char const * soundCharArray = getSound().c_str();
    NSString* soundName = [[[NSString alloc] initWithCString:soundCharArray encoding:NSUTF8StringEncoding] autorelease];
    if([soundName isEqualToString:@""] == FALSE && [soundName isEqualToString:_currentSoundName] == FALSE)
    {
        [_currentSoundName autorelease];
        _currentSoundName = [soundName retain];
        NSString* currentSoundPath = [[NSBundle mainBundle] pathForResource:_currentSoundName ofType:@"wav"];
        NSURL* currentSoundURL = [NSURL fileURLWithPath:currentSoundPath];
        printf("%s",[[currentSoundURL description] cStringUsingEncoding:NSUTF8StringEncoding]);
        AudioServicesDisposeSystemSoundID(_currentSoundID);
        AudioServicesCreateSystemSoundID((CFURLRef)currentSoundURL, &_currentSoundID);
        AudioServicesPlaySystemSound(_currentSoundID);

    }
}
 */

@end
