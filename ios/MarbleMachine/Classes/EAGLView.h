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

@end
