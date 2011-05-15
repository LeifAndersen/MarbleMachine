//
//  EAGLViewController.m
//  MarbleMachine
//
//  Created by Nathan Swenson on 5/13/11.
//  Copyright 2011 Nathan Swenson. All rights reserved.
//

#import "EAGLViewController.h"
#import "main.h"

@implementation EAGLViewController

- (id)init
{
    self = [super init];
    if (self) 
    {
        // Custom initialization
    }
    return self;
}

- (void)dealloc
{
    [super dealloc];
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle


// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView
{
    EAGLView* myView = [[[EAGLView alloc] initWithFrame:[[UIScreen mainScreen] applicationFrame]] autorelease];
    [self setView:myView];
    initGL();
    updateGL([myView renderbufferWidth], [myView renderbufferHeight]);
}

// Simply casts this view controller's view as an EAGLView for convenience.
- (EAGLView*) glView
{
    return (EAGLView*) [self view];
}


/*
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad
{
    [super viewDidLoad];
}
*/

- (void) drawGame
{
    [[self glView] startDraw];
    draw();
    [[self glView] commitDraw];
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return YES;
}

- (void) didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation
{
    updateGL([[self glView] renderbufferWidth], [[self glView] renderbufferHeight]);
}

@end
