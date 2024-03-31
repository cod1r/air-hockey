#include <SDL2/SDL.h>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#endif
#ifdef __LINUX__
#include <GL/gl.h>
#endif
#ifdef __WINDOWS__
#include <gl/GL.h>
#endif
#ifndef _OPENGL_FUNCTIONS_H
#define _OPENGL_FUNCTIONS_H
class OpenGLFunctions {
public:
  void (*glGetVertexAttribiv)(GLuint, GLenum , GLint *);
  void (*glGetVertexAttribfv)(GLuint, GLenum, GLfloat *);
  void (*glGetTexParameteriv)(GLenum, GLenum, GLint *);
  void (*glGetTexImage)(GLenum, GLint, GLenum, GLenum, void *);
  void (*glUniform1i)(GLint,GLint);
  void (*glActiveTexture)(GLenum);
  void (*glEnable)(GLenum);
  GLboolean (*glIsEnabled)(GLenum);
  GLboolean (*glIsTexture)(GLuint);
  void (*glTexParameterf)(GLenum, GLenum, GLfloat);
  void (*glTexParameteri)(GLenum, GLenum, GLint);
  void (*glGetUniformfv)(GLuint, GLint, GLfloat *);
  void (*glGetProgramiv)(GLuint, GLenum, GLint *);
  void (*glGetIntegerv)(GLenum, GLint *);
  void (*glGetActiveUniform)(GLuint, GLuint, GLsizei, GLsizei *, GLint *,
                             GLenum *, GLchar *);
  GLubyte *(*glGetString)(int);
  void (*glUniform4fv)(GLint, GLsizei, const GLfloat *);
  void (*glGenBuffers)(int, GLuint *);
  GLboolean (*glIsBuffer)(GLuint);
  GLboolean (*glIsProgram)(GLuint);
  void (*glBindBuffer)(GLenum, GLuint);
  void (*glGenTextures)(GLsizei, GLuint *);
  void (*glBindTexture)(GLenum, GLuint);
  void (*glClear)(GLbitfield);
  GLuint (*glCreateProgram)();
  GLuint (*glCreateShader)(GLenum);
  void (*glShaderSource)(GLuint, GLsizei, const GLchar **, const GLint *);
  void (*glCompileShader)(GLuint);
  void (*glAttachShader)(GLuint, GLuint);
  void (*glGetShaderInfoLog)(GLuint, GLsizei, GLsizei *, GLchar *);
  void (*glGetShaderiv)(GLuint, GLenum, GLint *);
  void (*glClearColor)(GLfloat, GLfloat, GLfloat, GLfloat);
  void (*glGetUniformiv)(GLuint, GLint, GLint *);
  GLint (*glGetUniformLocation)(GLuint, const GLchar *);
  void (*glTexImage2D)(GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum,
                       GLenum, const void *);
  void (*glLinkProgram)(GLuint);
  void (*glVertexAttribPointer)(GLuint, GLint, GLenum, GLboolean, GLsizei,
                                const void *);
  GLint (*glGetAttribLocation)(GLuint, const GLchar *);
  void (*glUseProgram)(GLuint);
  void (*glBufferData)(GLenum, GLsizei, const void *, GLenum);
  void (*glBufferSubData)(GLenum, GLint, GLsizei, const void *);
  void (*glDrawElements)(GLenum, GLsizei, GLenum, const void *);
  void (*glUniform4f)(GLint, GLfloat, GLfloat, GLfloat, GLfloat);
  GLenum (*glGetError)();
  void (*glEnableVertexAttribArray)(GLuint);
  void (*glGetBufferSubData)(GLenum, GLint, GLsizei, void *);
  void (*glGetNamedBufferSubData)(GLuint, GLint, GLsizei, void *);
  void (*glGetBufferParameteriv)(GLenum, GLenum, GLint *);
  void (*glGetNamedBufferParameteriv)(GLuint, GLenum, GLint *);
  OpenGLFunctions();
};
#endif
