#include "OpenGLFunctions.h"
#include "Renderer.h"
#include <GL/gl.h>
#include <iostream>
Renderer::Renderer()
{
    glFunctions = new OpenGLFunctions();
    GLuint hi = 0;
    glFunctions->glGenBuffers(1, &hi);
    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, hi);
    std::cout << (glFunctions->glIsBuffer(hi) == GL_TRUE ? "TRUE":"FALSE") << std::endl;
}