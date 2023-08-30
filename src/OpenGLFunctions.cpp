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
    glCreateShader = (GLuint (*)(GLenum))SDL_GL_GetProcAddress("glCreateShader");
    glShaderSource = (void (*)(GLuint, GLsizei, const GLchar**, const GLint*))SDL_GL_GetProcAddress("glShaderSource");
    glCompileShader = (void (*)(GLuint))SDL_GL_GetProcAddress("glCompileShader");
    glAttachShader = (void (*)(GLuint, GLuint))SDL_GL_GetProcAddress("glAttachShader");
    glGetShaderInfoLog = (void (*)(GLuint, GLsizei, GLsizei*, GLchar*))SDL_GL_GetProcAddress("glGetShaderInfoLog");
    glGetShaderiv = (void (*)(GLuint, GLenum, GLint*))SDL_GL_GetProcAddress("glGetShaderiv");
    glClearColor = (void (*)(GLfloat, GLfloat, GLfloat, GLfloat))SDL_GL_GetProcAddress("glClearColor");
    glGetUniformiv = (void (*)(GLuint, GLint, GLint*))SDL_GL_GetProcAddress("glGetUniformiv");
    glGetUniformLocation = (GLint (*)(GLuint, const GLchar *))SDL_GL_GetProcAddress("glGetUniformLocation");
}