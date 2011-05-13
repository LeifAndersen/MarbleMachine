//
//  MarbleMachineAppDelegate.h
//  MarbleMachine
//
//  Created by Nathan Swenson on 5/9/11.
//  Copyright 2011 Nathan Swenson. All rights reserved.
//

#import <AudioToolbox/AudioToolbox.h>

@class EAGLView;

@interface MarbleMachineAppDelegate : NSObject <UIApplicationDelegate> 
{
    UIWindow* _window;
    EAGLView* _glView;
    
    SystemSoundID _currentSoundID;
    NSString* _currentSoundName;
}

// This method should be called every draw cycle by an NSTimer and is responsible for telling the view to set up an opengl context,
// telling the C++ code to draw, and finally telling the view to commit the drawing.
- (void) drawGame;

@end
