#ifdef __APPLE__
#include <OpenGLES/ES2/gl.h>
#include <OpenGlES/ES2/glext.h>
#elif defined(ANDROID)
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#elif defined(linux)
#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES 1
#endif
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
#else 
#error "OpenGL include error: Y U NO HAVE COMPATIBLE OS?!"
#endif
