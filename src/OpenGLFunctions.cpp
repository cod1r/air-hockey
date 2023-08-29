#include "OpenGLFunctions.h"
OpenGLFunctions::OpenGLFunctions()
{
    glGenBuffers = (void (*)(int, GLuint*))SDL_GL_GetProcAddress("glGenBuffers");
    glGenVertexArrays = (void (*)(GLsizei, GLuint*))SDL_GL_GetProcAddress("glGenVertexArrays");
    glBindVertexArray = (void (*)(GLuint))SDL_GL_GetProcAddress("glBindVertexArray");
    glIsBuffer = (GLboolean (*)(GLuint))SDL_GL_GetProcAddress("glIsBuffer");
    glBindBuffer = (void (*)(GLenum, GLuint))SDL_GL_GetProcAddress("glBindBuffer");
    glGenTextures = (void (*)(GLsizei, GLuint*))SDL_GL_GetProcAddress("glGenTextures");
    glClear = (void (*)(GLbitfield))SDL_GL_GetProcAddress("glClear");
    glCreateProgram = (GLuint (*)())SDL_GL_GetProcAddress("glCreateProgram");
}