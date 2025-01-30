#ifndef _RENDERER_H
#define _RENDERER_H
#include "constants.h"
#include "OpenGLFunctions.h"
#include "qoi/qoi.h"
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
static const int TEXTURE_IDX = 2;
struct BufferObjectMetaData {
  GLint attrib_location;
  GLint size;
  GLint stride;
  GLboolean normalized;
  GLenum type;
};
class Renderer {
  std::vector<BufferObjectMetaData> buffer_info;
  std::vector<GLuint> vbos;
  std::vector<GLuint> ebos;
  std::vector<GLuint> textures;
  std::vector<GLuint> programs;
  GLuint vshdr;
  GLuint fshdr;

public:
  OpenGLFunctions *glFunctions = nullptr;
  SDL_Window *window = nullptr;
  qoi_desc desc;
  uint8_t *rgb_pixels = nullptr;
  Renderer();
  ~Renderer();
  void render();
  void read_shaders();
  void init_puck(std::vector<float> &);
  void init_paddle(std::vector<float> &);
  void init_table_texture();
  void update_puck_coords(const std::array<float, CONSTANTS::NUM_VERTICES> &);
  void update_paddle_coords(const std::array<float, CONSTANTS::NUM_VERTICES> &);
  void load_assets();
};
#endif
