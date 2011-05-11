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
    init(30, 30);
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
// This method should be called every draw cycle by an NSTimer and is responsible for getting the 
- (void) renderGame
{
    [_glView startDraw];
    draw();
    [_glView commitDraw];
}

@end
