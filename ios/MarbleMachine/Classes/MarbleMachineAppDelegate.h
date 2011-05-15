//
//  MarbleMachineAppDelegate.h
//  MarbleMachine
//
//  Created by Nathan Swenson on 5/9/11.
//  Copyright 2011 Nathan Swenson. All rights reserved.
//

#import <AudioToolbox/AudioToolbox.h>
#import "EAGLViewController.h"

@class EAGLView;

@interface MarbleMachineAppDelegate : NSObject <UIApplicationDelegate> 
{
    UIWindow* _window;
    
    SystemSoundID _currentSoundID;
    NSString* _currentSoundName;
    EAGLViewController* _gameController;
}

@end
