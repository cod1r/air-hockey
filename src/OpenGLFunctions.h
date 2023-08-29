#include <SDL2/SDL.h>
#include <GL/gl.h>
#ifndef _OPENGL_FUNCTIONS_H
#define _OPENGL_FUNCTIONS_H
class OpenGLFunctions {
    public:
        void (*glGenBuffers)(int, GLuint*) ;
        void (*glGenVertexArrays)(GLsizei, GLuint*) ;
        void (*glBindVertexArray)(GLuint) ;
        GLboolean (*glIsBuffer)(GLuint) ;
        void (*glBindBuffer)(GLenum, GLuint) ;
        void (*glGenTextures)(GLsizei, GLuint*) ;
        void (*glClear)(GLbitfield) ;
        GLuint (*glCreateProgram)() ;
        GLuint (*glCreateShader)(GLenum) ;
        void (*glShaderSource)(GLuint, GLsizei, const GLchar**, const GLint*) ;
        void (*glCompileShader)(GLuint);
        void (*glAttachShader)(GLuint, GLuint);
        void (*glGetShaderInfoLog)(GLuint, GLsizei, GLsizei*, GLchar*);
        void (*glGetShaderiv)(GLuint, GLenum, GLint*);
        OpenGLFunctions();
};
#endif