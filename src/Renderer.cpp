#include "OpenGLFunctions.h"
#include "Renderer.h"
#include <GL/gl.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
Renderer::Renderer()
{
    glFunctions = new OpenGLFunctions();
    read_shaders();
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
        std::string vshdr_contents;
        while (!vsh.eof()) {
            vshdr_contents += vsh.get();
        }
        vshdr = glFunctions->glCreateShader(GL_VERTEX_SHADER);
        const GLchar *shdr_cstr = vshdr_contents.c_str();
        glFunctions->glShaderSource(vshdr, 1, &shdr_cstr, NULL);
        glFunctions->glCompileShader(vshdr);
        GLint status;
        glFunctions->glGetShaderiv(vshdr, GL_COMPILE_STATUS, &status);
        if (status != GL_TRUE) {
            GLsizei length;
            GLchar buffer[1024];
            glFunctions->glGetShaderInfoLog(vshdr, 1024, &length, buffer);
            std::cerr << buffer << std::endl;
        }
    }
}