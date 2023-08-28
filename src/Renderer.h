#ifndef _RENDERER_H
#define _RENDERER_H
class OpenGLFunctions;
class Renderer {
    OpenGLFunctions *glFunctions = nullptr;
public:
    Renderer();
    ~Renderer();
};
#endif