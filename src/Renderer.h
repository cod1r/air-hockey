#ifndef _RENDERER_H
#define _RENDERER_H
#include "OpenGLFunctions.h"
#include <SDL2/SDL.h>
#include <vector>
#define GET_GL_ERROR()                                                         \
  GLenum err = glFunctions->glGetError();                                      \
  switch (err) {                                                               \
  case GL_INVALID_ENUM:                                                        \
    std::cerr << "GL_INVALID_ENUM\n";                                          \
    throw;                                                                     \
    break;                                                                     \
  case GL_INVALID_VALUE:                                                       \
    std::cerr << "GL_INVALID_VALUE\n";                                         \
    throw;                                                                     \
    break;                                                                     \
  case GL_INVALID_OPERATION:                                                   \
    std::cerr << "GL_INVALID_OPERATION\n";                                     \
    throw;                                                                     \
    break;                                                                     \
  case GL_STACK_OVERFLOW:                                                      \
    std::cerr << "GL_STACK_OVERFLOW\n";                                        \
    throw;                                                                     \
    break;                                                                     \
  case GL_STACK_UNDERFLOW:                                                     \
    std::cerr << "GL_STACK_UNDERFLOW\n";                                       \
    throw;                                                                     \
    break;                                                                     \
  case GL_OUT_OF_MEMORY:                                                       \
    std::cerr << "GL_OUT_OF_MEMORY\n";                                         \
    throw;                                                                     \
    break;                                                                     \
  case GL_TABLE_TOO_LARGE:                                                     \
    std::cerr << "GL_TABLE_TOO_LARGE\n";                                       \
    throw;                                                                     \
    break;                                                                     \
  case GL_NO_ERROR:                                                            \
    break;                                                                     \
  }
class OpenGLFunctions;
static const int PUCK_IDX = 0;
static const int PADDLE_IDX = 1;
struct BufferObjectMetaData {
  GLint attrib_location;
  GLint size;
  GLint stride;
  GLboolean normalized;
  GLenum type;
};
class Renderer {
  std::vector<BufferObjectMetaData> buffer_info;
  std::vector<std::vector<GLuint>> vbos;
  std::vector<std::vector<GLuint>> ebos;
  std::vector<GLuint> programs;
  GLuint vshdr;
  GLuint fshdr;

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
  void update_puck_inter_coords(std::vector<float> &);
  void load_assets();
};
#endif
