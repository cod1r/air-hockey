#include <SDL2/SDL.h>
#include <GL/gl.h>
#ifndef _OPENGL_FUNCTIONS_H
#define _OPENGL_FUNCTIONS_H
class OpenGLFunctions {
    public:
        void (*glGenBuffers)(int, GLuint*) = nullptr;
        void (*glGenVertexArrays)(GLsizei, GLuint*) = nullptr;
        void (*glBindVertexArray)(GLuint) = nullptr;
        GLboolean (*glIsBuffer)(GLuint) = nullptr;
        void (*glBindBuffer)(GLenum, GLuint) = nullptr;
        void (*glGenTextures)(GLsizei, GLuint*) = nullptr;
        void (*glClear)(GLbitfield) = nullptr;
        GLuint (*glCreateProgram)() = nullptr;
        OpenGLFunctions();
};
#endif