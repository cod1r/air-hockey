#include "OpenGLFunctions.h"
OpenGLFunctions::OpenGLFunctions()
{
    glGenBuffers = (void (*)(int, GLuint*))SDL_GL_GetProcAddress("glGenBuffers");
    glIsBuffer = (GLboolean (*)(GLuint))SDL_GL_GetProcAddress("glIsBuffer");
    glBindBuffer = (void (*)(GLenum, GLuint))SDL_GL_GetProcAddress("glBindBuffer");
}