//
//  EAGLViewController.h
//  MarbleMachine
//
//  Created by Nathan Swenson on 5/13/11.
//  Copyright 2011 Nathan Swenson. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "EAGLView.h"

@interface EAGLViewController : UIViewController 
{
    
}

// Creates the glView and sets its frame to be the applicationFrame. Normally its a bad idea to set the view's frame here, but
// in the case of an OpenGL view, setting its frame after the fact is somewhat nasty business, and its a pretty safe assumption that
// the game view should take up the full screen. Maybe this should be changed at some point in the future though.
- (void) loadView;

// The OpenGL view that this controller uses to set up OpenGL and draw the game.
@property (nonatomic, readonly) EAGLView* glView;

// Communicates with the C++ code to render the game. Should be called repeatedly.
- (void) drawGame;

@end
