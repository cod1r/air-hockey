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
    } else {
        std::cerr << "vertex shader could not be opened" << std::endl;
        throw;
    }
    vsh.close();
    std::filesystem::path fsh_path(std::string("shaders/frag.glsl"));
    std::ifstream fsh;
    fsh.open(fsh_path.c_str());
    if (fsh.is_open()) {
        std::string fshdr_contents;
        while (!fsh.eof()) {
            fshdr_contents += fsh.get();
        }
        fshdr = glFunctions->glCreateShader(GL_VERTEX_SHADER);
        const GLchar *shdr_cstr = fshdr_contents.c_str();
        glFunctions->glShaderSource(fshdr, 1, &shdr_cstr, NULL);
        glFunctions->glCompileShader(fshdr);
        GLint status;
        glFunctions->glGetShaderiv(fshdr, GL_COMPILE_STATUS, &status);
        if (status != GL_TRUE) {
            GLsizei length;
            GLchar buffer[1024];
            glFunctions->glGetShaderInfoLog(fshdr, 1024, &length, buffer);
            std::cerr << buffer << std::endl;
        }
    } else {
        std::cerr << "fragment shader could not be opened" << std::endl;
        throw;
    }
}