//
//  EAGLView.m
//  MarbleMachine
//
//  Created by Nathan Swenson on 5/9/11.
//  Copyright Nathan Swenson 2011. All rights reserved.
//

#import "EAGLView.h"

// Attribute Index used to identify attribute arrays
enum EAGLViewAttribute
{
    EAGLViewAttributeVertex,
	EAGLViewAttributeNormal,
    EAGLViewAttributeTextureCoordinate,
    EAGLViewAttributeAttributeCount
};
typedef enum EAGLViewAttribute EAGLViewAttribute;

#pragma mark Private Interface
@interface EAGLView ()
@end

#pragma mark -
@implementation EAGLView

#pragma mark -
#pragma mark UIView Class Methods
+ (Class) layerClass
{
    return [CAEAGLLayer class];
}

#pragma mark -
#pragma mark Constructors
- (id) initWithFrame:(CGRect)frame
{
	self = [super initWithFrame:frame];
	if (self == nil)
		return nil;
	
	// Apply scaling factor for high-resolution screens
	if ([self respondsToSelector:@selector(setContentScaleFactor:)] && [[UIScreen mainScreen] respondsToSelector:@selector(scale)])
        [self setContentScaleFactor:[[UIScreen mainScreen] scale]];
    
    // Setup an OpenGL rendering layer from the view's CALayer
    CAEAGLLayer* eaglLayer = (CAEAGLLayer*)[self layer];
    [eaglLayer setOpaque:TRUE];
    [eaglLayer setDrawableProperties:[NSDictionary dictionaryWithObjectsAndKeys:
        [NSNumber numberWithBool:FALSE], 
        kEAGLDrawablePropertyRetainedBacking, 
        kEAGLColorFormatRGBA8, 
        kEAGLDrawablePropertyColorFormat, 
        nil]];
    
    // Create an OpenGL rendering context
    _context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    if (!_context || ![EAGLContext setCurrentContext:_context]) 
        return nil;
    
    // Allocate frame and render buffer IDs
    glGenFramebuffers(1, &_viewFramebuffer);
    glGenRenderbuffers(1, &_viewRenderbuffer);
    
    // Create frame and render buffers
    glBindFramebuffer(GL_FRAMEBUFFER, _viewFramebuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _viewRenderbuffer);
    [_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:(CAEAGLLayer*)[self layer]];
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _viewRenderbuffer);
    
    // Get size of view from API (should be the same as the frame parameter)
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &_viewportWidth);
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &_viewportHeight);
    
    // Create depth buffer
    glGenRenderbuffers(1, &_viewDepthRenderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _viewDepthRenderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, _viewportWidth, _viewportHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _viewDepthRenderbuffer);
    
    // Check for successful creation
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) 
        return nil;
    
    // Create and compile vertex shader
    NSString* vertexShaderPath = [[NSBundle mainBundle] pathForResource:@"Shader" ofType:@"vsh"];
    NSString* vertexShaderSourceString = 
		[NSString stringWithContentsOfFile:vertexShaderPath encoding:NSUTF8StringEncoding error:nil];
	GLchar* vertexShaderSource = (GLchar*)[vertexShaderSourceString UTF8String];
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, (const GLchar**)&vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	
	// Check vertex shader compilation log
	GLint vertexShaderCompileLogLength = 0;
	glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &vertexShaderCompileLogLength);
	if (vertexShaderCompileLogLength > 0)
	{
		GLchar* vertexShaderLog = (GLchar*)malloc(vertexShaderCompileLogLength);
		glGetShaderInfoLog(vertexShader, vertexShaderCompileLogLength, &vertexShaderCompileLogLength, vertexShaderLog);
		NSLog(@"Vertex Shader compile log:\n%s", vertexShaderLog);
		free(vertexShaderLog);
	}
	
	// Check vertex shader compilation status
	GLint vertexShaderCompileStatus = GL_FALSE;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexShaderCompileStatus);
	if (vertexShaderCompileStatus == GL_FALSE)
	{
		glDeleteShader(vertexShader);
		return nil;
	}	

	// Create and compile fragment shader
    NSString* fragmentShaderPath = [[NSBundle mainBundle] pathForResource:@"Shader" ofType:@"fsh"];
    NSString* fragmentShaderSourceString = 
		[NSString stringWithContentsOfFile:fragmentShaderPath encoding:NSUTF8StringEncoding error:nil];
	GLchar* fragmentShaderSource = (GLchar*)[fragmentShaderSourceString UTF8String];
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	
	// Check fragment shader compilation log
	GLint fragmentShaderCompileLogLength = 0;
	glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &fragmentShaderCompileLogLength);
	if (fragmentShaderCompileLogLength > 0)
	{
		GLchar* fragmentShaderLog = (GLchar*)malloc(fragmentShaderCompileLogLength);
		glGetShaderInfoLog(fragmentShader, fragmentShaderCompileLogLength, &fragmentShaderCompileLogLength, fragmentShaderLog);
		NSLog(@"Fragment Shader compile log:\n%s", fragmentShaderLog);
		free(fragmentShaderLog);
	}
	
	// Check fragment shader compilation status
	GLint fragmentShaderCompileStatus = GL_FALSE;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentShaderCompileStatus);
	if (fragmentShaderCompileStatus == GL_FALSE)
	{
		glDeleteShader(fragmentShader);
		return nil;
	}

	// Create shader program then attach vertex and fragment shaders
    _program = glCreateProgram();
    glAttachShader(_program, vertexShader);
    glAttachShader(_program, fragmentShader);

    // Bind attribute variable locations, which needs to be done prior to linking
    glBindAttribLocation(_program, EAGLViewAttributeVertex, "position");
    glBindAttribLocation(_program, EAGLViewAttributeNormal, "normal");
	glBindAttribLocation(_program, EAGLViewAttributeTextureCoordinate, "textureCoordinate");

    // Link program, then release vertex and fragment shaders, which are not needed after linking the program
    glLinkProgram(_program);
	glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
	
	// Check program link log
	GLint programLogLength;
	glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &programLogLength);
	if (programLogLength > 0)
	{
		GLchar* programLog = (GLchar *)malloc(programLogLength);
		glGetProgramInfoLog(_program, programLogLength, &programLogLength, programLog);
		NSLog(@"Program link log:\n%s", programLog);
		free(programLog);
	}
	
	// Check program link status
	GLint programLinkStatus = GL_FALSE;
	glGetProgramiv(_program, GL_LINK_STATUS, &programLinkStatus);
	if (programLinkStatus == GL_FALSE)
	{
		NSLog(@"Failed to link program: %d", _program);
		glDeleteProgram(_program);
		_program = 0;
        return nil;
	}
	
    // Setup uniform variables by getting their locations (on the graphics hardware) and setting default values (on the CPU)
    _modelViewUniformLocation = glGetUniformLocation(_program, "modelView");
	_modelView = CATransform3DIdentity;
	_projectionUniformLocation = glGetUniformLocation(_program, "projection");
	_projection = CATransform3DIdentity;
	
	_lightPositionUniformLocation = glGetUniformLocation(_program, "lightPosition");
	_lightPosition[0] = 0.2f;
	_lightPosition[1] = 0.0f;
	_lightPosition[2] = 1.0f;
	_lightPosition[3] = 1.0f;
	
	_lightAmbientUniformLocation = glGetUniformLocation(_program, "lightAmbient");
	_lightAmbient[0] = 0.3f;
	_lightAmbient[1] = 0.3f;
	_lightAmbient[2] = 0.3f;
	_lightAmbient[3] = 1.0f;
	
	_lightDiffuseUniformLocation = glGetUniformLocation(_program, "lightDiffuse");
	_lightDiffuse[0] = 1.0f;
	_lightDiffuse[1] = 1.0f;
	_lightDiffuse[2] = 1.0f;
	_lightDiffuse[3] = 1.0f;
	
	_textureNumberUniformLocation = glGetUniformLocation(_program, "textureNumber");
	_textureNumber = 0;
	
	// Load textures
	GLubyte textureData[] = 
	{
		0x22, 0x2D, 0x69, 0xFF, 0x22, 0x2D, 0x6D, 0xFF, 0x1B, 0x2A, 0x6F, 0xFF, 0x21, 0x2C, 0x66, 0xFF,
		0x1F, 0x2B, 0x66, 0xFF, 0x18, 0x28, 0x6F, 0xFF, 0x22, 0x2E, 0x6D, 0xFF, 0x25, 0x30, 0x71, 0xFF,
		0x22, 0x2D, 0x6D, 0xFF, 0x26, 0x32, 0x71, 0xFF, 0x54, 0x52, 0x46, 0xFF, 0x7D, 0x76, 0x3F, 0xFF,
		0x84, 0x7D, 0x3F, 0xFF, 0x5E, 0x5B, 0x47, 0xFF, 0x22, 0x2F, 0x6F, 0xFF, 0x29, 0x36, 0x7B, 0xFF,
		0x1A, 0x29, 0x6F, 0xFF, 0x59, 0x58, 0x4D, 0xFF, 0x82, 0x76, 0x00, 0xFF, 0xC7, 0xC4, 0xA7, 0xFF,
		0xD4, 0xCF, 0xA7, 0xFF, 0xA8, 0x99, 0x00, 0xFF, 0x65, 0x61, 0x4B, 0xFF, 0x1E, 0x2E, 0x7D, 0xFF,
		0x25, 0x2F, 0x67, 0xFF, 0x75, 0x6F, 0x34, 0xFF, 0xB8, 0xAB, 0x6A, 0xFF, 0xB7, 0xC2, 0xA6, 0xFF,
		0xC6, 0xD0, 0xAD, 0xFF, 0xE2, 0xD4, 0x6C, 0xFF, 0x96, 0x8D, 0x34, 0xFF, 0x24, 0x31, 0x75, 0xFF,
		0x1F, 0x2A, 0x65, 0xFF, 0x80, 0x79, 0x3B, 0xFF, 0xF2, 0xEC, 0xDD, 0xFF, 0x95, 0xB1, 0x8B, 0xFF,
		0xA4, 0xBD, 0x97, 0xFF, 0xFF, 0xFE, 0xDE, 0xFF, 0xAB, 0xA0, 0x3A, 0xFF, 0x1C, 0x2B, 0x74, 0xFF,
		0x17, 0x27, 0x70, 0xFF, 0x5A, 0x56, 0x3E, 0xFF, 0xEB, 0xE6, 0xD0, 0xFF, 0xB6, 0xCB, 0xB1, 0xFF,
		0xBF, 0xD2, 0xB9, 0xFF, 0xFF, 0xF9, 0xD2, 0xFF, 0x7C, 0x75, 0x3C, 0xFF, 0x0E, 0x26, 0x7E, 0xFF,
		0x24, 0x2F, 0x6E, 0xFF, 0x1C, 0x2A, 0x6D, 0xFF, 0x63, 0x5F, 0x45, 0xFF, 0xAD, 0xA7, 0x84, 0xFF,
		0xB8, 0xB1, 0x83, 0xFF, 0x7F, 0x78, 0x47, 0xFF, 0x13, 0x25, 0x6A, 0xFF, 0x2C, 0x37, 0x7C, 0xFF,
		0x23, 0x2F, 0x70, 0xFF, 0x26, 0x33, 0x78, 0xFF, 0x13, 0x27, 0x77, 0xFF, 0x06, 0x1D, 0x65, 0xFF,
		0x01, 0x1C, 0x66, 0xFF, 0x00, 0x1F, 0x78, 0xFF, 0x26, 0x32, 0x77, 0xFF, 0x46, 0x51, 0x95, 0xFF,
	};
	GLuint textureId = 0;
	glEnable(GL_TEXTURE);
	glGenTextures(1, &textureId);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 
		(GLsizei)sqrtf(sizeof(textureData) / sizeof(GLuint)), 
		(GLsizei)sqrtf(sizeof(textureData) / sizeof(GLuint)), 
		0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
	
	// Create models
	//TODO: This!
    
    // Start animation
    [NSTimer scheduledTimerWithTimeInterval:1.0f / 60.0f 
        target:self 
        selector:@selector(startDraw) 
        userInfo:nil 
        repeats:YES];
    
	return self;
} 

- (void) dealloc
{
    // Deallocate video buffers
    glDeleteFramebuffers(1, &_viewFramebuffer);
    _viewFramebuffer = 0;
    glDeleteRenderbuffers(1, &_viewRenderbuffer);
    _viewRenderbuffer = 0;
    glDeleteRenderbuffers(1, &_viewDepthRenderbuffer);
    _viewDepthRenderbuffer = 0;
    
	// Deallocate shader program
	glDeleteProgram(_program);
	_program = 0;
	
    [super dealloc];
}

#pragma mark -
#pragma mark EAGLView Methods
- (void) startDraw
{
	// Setup OpenGL Context
    [EAGLContext setCurrentContext:_context];
    glBindFramebuffer(GL_FRAMEBUFFER, _viewFramebuffer);
    glViewport(0, 0, _viewportWidth, _viewportHeight);
    
	// Clear frame buffer
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

- (void) commitDraw
{
	// Present rendered data
    glBindRenderbuffer(GL_RENDERBUFFER, _viewRenderbuffer);
    [_context presentRenderbuffer:GL_RENDERBUFFER];
}

@end
