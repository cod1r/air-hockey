#include <vector>
#include <GL/gl.h>
#ifndef _RENDERER_H
#define _RENDERER_H
class OpenGLFunctions;
class Renderer {
    std::vector<GLuint> vaos;
    std::vector<std::vector<GLuint>> vbos;
    std::vector<GLuint> programs;
public:
    OpenGLFunctions *glFunctions = nullptr;
    Renderer();
    ~Renderer();
    void render();
    void read_shaders();
};
#endif