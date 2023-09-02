#include <vector>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#ifndef _RENDERER_H
#define _RENDERER_H
class OpenGLFunctions;
class Renderer {
    std::vector<GLuint> vaos;
    std::vector<std::vector<GLuint>> vbos;
    std::vector<std::vector<GLuint>> ebos;
    std::vector<GLuint> programs;
    GLuint vshdr;
    GLuint fshdr;
    size_t puck_array_buffer_idx;
    size_t paddle_array_buffer_idx;
public:
    OpenGLFunctions *glFunctions = nullptr;
    SDL_Window *window = nullptr;
    SDL_Surface *texture_atlas = nullptr;
    Renderer();
    ~Renderer();
    void render();
    void read_shaders();
    void init_puck(std::vector<float> &);
    void init_paddle(std::vector<float> &);
    void update_puck_coords(std::vector<float> &);
    void update_paddle_coords(std::vector<float> &);
    void load_assets();
};
#endif