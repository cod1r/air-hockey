#include <SDL2/SDL.h>
#include <GL/gl.h>
#ifndef _OPENGL_FUNCTIONS_H
#define _OPENGL_FUNCTIONS_H
class OpenGLFunctions {
    public:
        void (*glGenBuffers)(int, GLuint*) = nullptr;
        GLboolean (*glIsBuffer)(GLuint) = nullptr;
        void (*glBindBuffer)(GLenum, GLuint) = nullptr;
        OpenGLFunctions();
};
#endif