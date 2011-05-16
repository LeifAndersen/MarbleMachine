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
    // Create window and OpenGL view controller, and add the controller's view to the window.
	_window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
	_gameController = [[EAGLViewController alloc] init];
	[_window addSubview:[_gameController view]];
	[_window makeKeyAndVisible];
    
    // Sets up the draw loop to be run at intervals.
    [NSTimer scheduledTimerWithTimeInterval:1.0f/30.0f target:_gameController selector:@selector(drawGame) userInfo:nil repeats:YES];
    
    // Initialize some needed variables
    _currentSoundID = 0;
    _currentSoundName = [@"" retain];
}

- (void) applicationWillTerminate:(UIApplication*)application 
{
	[_window release];
	[_gameController release];
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


@end
