#ifdef ANDROID
    #include <GLES2/gl2.h>
    #include <GLES2/gl2ext.h>
    #define __GLES__
#elif linux
    #ifndef GL_GLEXT_PROTOTYPES
        #define GL_GLEXT_PROTOTYPES 1
    #endif
    #include <GL/gl.h>
    #include <GL/glext.h>
    #include <GL/glu.h>
#elif _WIN32
    #include <windows.h>
    #ifndef GL_GLEXT_PROTOTYPES
        #define GL_GLEXT_PROTOTYPES 1
    #endif
    #include <GL/gl.h>
    #include <GL/glext.h>
    #include <GL/glu.h>
#elif __APPLE__
    #include "TargetConditionals.h"
    //#ifdef TARGET_OS_IPHONE
    //    #include <OpenGLES/ES2/gl.h>
    //    #include <OpenGlES/ES2/glext.h>
    //    #define __GLES__
    //#elif TARGET_IPHONE_SIMULATOR
    //    #include <OpenGLES/ES2/gl.h>
    //    #include <OpenGlES/ES2/glext.h>
    //    #define __GLES__
    //#elif TARGET_OS_MAC
        #ifndef GL_GLEXT_PROTOTYPES
            #define GL_GLEXT_PROTOTYPES 1
        #endif
        #include <OpenGL/gl.h>
        #include <OpenGL/glext.h>
        #include <OpenGL/glu.h>
    //#endif
#else
    #error "OpenGL include error: Y U NO HAVE COMPATIBLE OS?!"
#endif
