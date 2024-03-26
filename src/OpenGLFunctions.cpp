#include "OpenGLFunctions.h"
OpenGLFunctions::OpenGLFunctions() {
  glTexParameterf = (void (*)(GLenum, GLenum, GLfloat))SDL_GL_GetProcAddress(
      "glTexParameterf");
  glTexParameteri =
      (void (*)(GLenum, GLenum, GLint))SDL_GL_GetProcAddress("glTexParameteri");
  glGetProgramiv = (void (*)(GLuint, GLenum, GLint *))SDL_GL_GetProcAddress(
      "glGetProgramiv");
  glGetIntegerv =
      (void (*)(GLenum, GLint *))SDL_GL_GetProcAddress("glGetIntegerv");
  glGetActiveUniform =
      (void (*)(GLuint, GLuint, GLsizei, GLsizei *, GLint *, GLenum *,
                GLchar *))SDL_GL_GetProcAddress("glGetActiveUniform");
  glUniform4fv = (void (*)(
      GLint, GLsizei, const GLfloat *))SDL_GL_GetProcAddress("glUniform4fv");
  glGetString = (GLubyte * (*)(int)) SDL_GL_GetProcAddress("glGetString");
  glGenBuffers = (void (*)(int, GLuint *))SDL_GL_GetProcAddress("glGenBuffers");
  glIsBuffer = (GLboolean(*)(GLuint))SDL_GL_GetProcAddress("glIsBuffer");
  glIsProgram = (GLboolean(*)(GLuint))SDL_GL_GetProcAddress("glIsProgram");
  glBindBuffer =
      (void (*)(GLenum, GLuint))SDL_GL_GetProcAddress("glBindBuffer");
  glGenTextures =
      (void (*)(GLsizei, GLuint *))SDL_GL_GetProcAddress("glGenTextures");
  glBindTexture =
      (void (*)(GLenum, GLuint))SDL_GL_GetProcAddress("glBindTexture");
  glTexImage2D =
      (void (*)(GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum,
                const void *))SDL_GL_GetProcAddress("glTexImage2D");
  glClear = (void (*)(GLbitfield))SDL_GL_GetProcAddress("glClear");
  glCreateProgram = (GLuint(*)())SDL_GL_GetProcAddress("glCreateProgram");
  glCreateShader = (GLuint(*)(GLenum))SDL_GL_GetProcAddress("glCreateShader");
  glShaderSource =
      (void (*)(GLuint, GLsizei, const GLchar **,
                const GLint *))SDL_GL_GetProcAddress("glShaderSource");
  glCompileShader = (void (*)(GLuint))SDL_GL_GetProcAddress("glCompileShader");
  glAttachShader =
      (void (*)(GLuint, GLuint))SDL_GL_GetProcAddress("glAttachShader");
  glGetShaderInfoLog =
      (void (*)(GLuint, GLsizei, GLsizei *, GLchar *))SDL_GL_GetProcAddress(
          "glGetShaderInfoLog");
  glGetShaderiv =
      (void (*)(GLuint, GLenum, GLint *))SDL_GL_GetProcAddress("glGetShaderiv");
  glClearColor = (void (*)(GLfloat, GLfloat, GLfloat,
                           GLfloat))SDL_GL_GetProcAddress("glClearColor");
  glGetUniformfv = (void (*)(GLuint, GLint, GLfloat *))SDL_GL_GetProcAddress(
      "glGetUniformfv");
  glGetUniformiv =
      (void (*)(GLuint, GLint, GLint *))SDL_GL_GetProcAddress("glGetUniformiv");
  glGetUniformLocation = (GLint(*)(
      GLuint, const GLchar *))SDL_GL_GetProcAddress("glGetUniformLocation");
  glLinkProgram = (void (*)(GLuint))SDL_GL_GetProcAddress("glLinkProgram");
  glVertexAttribPointer =
      (void (*)(GLuint, GLint, GLenum, GLboolean, GLsizei,
                const void *))SDL_GL_GetProcAddress("glVertexAttribPointer");
  glGetAttribLocation = (GLint(*)(GLuint, const GLchar *))SDL_GL_GetProcAddress(
      "glGetAttribLocation");
  glUseProgram = (void (*)(GLuint))SDL_GL_GetProcAddress("glUseProgram");
  glBufferData = (void (*)(GLenum, GLsizei, const void *,
                           GLenum))SDL_GL_GetProcAddress("glBufferData");
  glBufferSubData =
      (void (*)(GLenum, GLint, GLsizei, const void *))SDL_GL_GetProcAddress(
          "glBufferSubData");
  glDrawElements =
      (void (*)(GLenum, GLsizei, GLenum, const void *))SDL_GL_GetProcAddress(
          "glDrawElements");
  glUniform4f = (void (*)(GLint, GLfloat, GLfloat, GLfloat,
                          GLfloat))SDL_GL_GetProcAddress("glUniform4f");
  glGetError = (GLenum(*)())SDL_GL_GetProcAddress("glGetError");
  glEnableVertexAttribArray =
      (void (*)(GLuint))SDL_GL_GetProcAddress("glEnableVertexAttribArray");
  glGetBufferSubData =
      (void (*)(GLenum, GLint, GLsizei, void *))SDL_GL_GetProcAddress(
          "glGetBufferSubData");
  glGetNamedBufferSubData =
      (void (*)(GLuint, GLint, GLsizei, void *))SDL_GL_GetProcAddress(
          "glGetNamedBufferSubData");
  glGetBufferParameteriv = (void (*)(
      GLenum, GLenum, GLint *))SDL_GL_GetProcAddress("glGetBufferParameteriv");
  glGetNamedBufferParameteriv =
      (void (*)(GLuint, GLenum, GLint *))SDL_GL_GetProcAddress(
          "glGetNamedBufferParameteriv");
}
