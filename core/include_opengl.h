#ifdef __APPLE__
#include <OpenGLES/ES2/gl.h>
#include <OpenGlES/ES2/glext.h>
#elif defined(ANDROID)
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#else 
#error "OpenGL include error: Y U NO HAVE COMPATIBLE OS?!"
#endif