#include "OpenGLFunctions.h"
#include "Renderer.h"
#include <GL/gl.h>
#include <iostream>
#include <fstream>
#include <filesystem>
Renderer::Renderer()
{
    glFunctions = new OpenGLFunctions();
}
void Renderer::render()
{
    glFunctions->glClear(GL_COLOR_BUFFER_BIT);
}
void Renderer::read_shaders()
{
    std::filesystem::path vsh_path(std::string("shaders/vtx.glsl"));
    std::ifstream vsh;
    vsh.open(vsh_path.c_str());
    if (vsh.is_open()) {
    }
}