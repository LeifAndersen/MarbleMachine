//
//  EAGLView.h
//  MarbleMachine
//
//  Created by Nathan Swenson on 5/9/11.
//  Copyright Nathan Swenson 2011. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#import <QuartzCore/QuartzCore.h>

@interface EAGLView : UIView 
{
    EAGLContext* _context;
	
    GLint _viewportWidth;
    GLint _viewportHeight;
	
	GLuint _viewRenderbuffer;
    GLuint _viewFramebuffer;
    GLuint _viewDepthRenderbuffer;
	
	GLuint _program;
	
	GLuint _modelViewUniformLocation;
	CATransform3D _modelView;
	GLuint _projectionUniformLocation;
	CATransform3D _projection;
	
	GLuint _lightPositionUniformLocation;
	float _lightPosition[4];
	GLuint _lightAmbientUniformLocation;
	float _lightAmbient[4];
	GLuint _lightDiffuseUniformLocation;
	float _lightDiffuse[4];
	
	GLuint _textureNumberUniformLocation;
	GLint _textureNumber;
}

// Sets up the OpenGLES context and gets everything ready so that OpenGLES calls can start being made.
- (void) startDraw;

// After some other code is done with all its OpenGLES calls for this "frame", call this method to present the frame to the user.
- (void) commitDraw;

// Gives the width of the OpenGL render buffer. Use this when you need the view's width in pixels rather than points.
@property(nonatomic, readonly) GLint renderbufferWidth;

// Gives the height of the OpenGL render buffer. Use this when you need the view's height in pixels rather than points.
@property(nonatomic, readonly) GLint renderbufferHeight;

@end
