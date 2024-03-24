#include "Renderer.h"
#include "AirHockey.h"
#include "OpenGLFunctions.h"
#include "constants.h"
#include <SDL2/SDL_image.h>
#include <array>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
Renderer::Renderer() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << SDL_GetError() << std::endl;
    throw;
  }
  window =
      SDL_CreateWindow("AirHockey", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
                       SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS |
                           SDL_WINDOW_INPUT_GRABBED | SDL_WINDOW_ALLOW_HIGHDPI);
  if (window == NULL) {
    std::cout << SDL_GetError() << std::endl;
    throw;
  }
  SDL_GLContext ctx = SDL_GL_CreateContext(window);
  if (SDL_GL_MakeCurrent(window, ctx) < 0) {
    std::cout << SDL_GetError() << std::endl;
    throw;
  }
  glFunctions = new OpenGLFunctions();
  read_shaders();
  GLuint puck_program = glFunctions->glCreateProgram();
  glFunctions->glAttachShader(puck_program, vshdr);
  glFunctions->glAttachShader(puck_program, fshdr);
  glFunctions->glLinkProgram(puck_program);
  programs.push_back(puck_program);
  GLuint paddle_program = glFunctions->glCreateProgram();
  glFunctions->glAttachShader(paddle_program, vshdr);
  glFunctions->glAttachShader(paddle_program, fshdr);
  glFunctions->glLinkProgram(paddle_program);
  programs.push_back(paddle_program);
}
void Renderer::render() {
  glFunctions->glClearColor(1, 1, 1, 1);
  glFunctions->glClear(GL_COLOR_BUFFER_BIT);

  glFunctions->glUseProgram(programs.at(PUCK_IDX));
  glFunctions->glBindVertexArray(vaos.at(PUCK_IDX));
  glFunctions->glDrawElements(GL_TRIANGLES, NUM_SIDES * 3, GL_UNSIGNED_INT, 0);

  // glFunctions->glUseProgram(programs.at(PUCK_IDX));
  // glFunctions->glBindVertexArray(vaos.at(2));
  // glFunctions->glDrawElements(GL_TRIANGLES, NUM_SIDES * 3, GL_UNSIGNED_INT,
  // 0);

  glFunctions->glUseProgram(programs.at(PADDLE_IDX));
  glFunctions->glBindVertexArray(vaos.at(PADDLE_IDX));
  glFunctions->glDrawElements(GL_TRIANGLES, NUM_SIDES * 3, GL_UNSIGNED_INT, 0);
  SDL_GL_SwapWindow(window);
}
void Renderer::read_shaders() {
  std::cerr << "OPENGL VERSION: " << glFunctions->glGetString(GL_VERSION) << std::endl;
  std::filesystem::path vsh_path(std::string("shaders/vtx.glsl"));
  std::ifstream vsh;
  vsh.open(vsh_path.c_str());
  if (vsh.is_open()) {
    std::cerr << "Reading vertex shader\n";
    std::string vshdr_contents;
    int count = 0;
    while (!vsh.eof()) {
      vshdr_contents += vsh.get();
      count++;
    }
    vshdr = glFunctions->glCreateShader(GL_VERTEX_SHADER);
    const GLchar *shdr_cstr = vshdr_contents.c_str();
    int sizes[] = { (int)vshdr_contents.length() - 1 };
    glFunctions->glShaderSource(vshdr, 1, &shdr_cstr, sizes);
    glFunctions->glCompileShader(vshdr);
    GLint status;
    glFunctions->glGetShaderiv(vshdr, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
      GLsizei length;
      GLchar buffer[1024];
      glFunctions->glGetShaderInfoLog(vshdr, 1024, &length, buffer);
      std::cerr << buffer << std::endl;
      throw;
    }
  } else {
    std::cerr << "vertex shader could not be opened" << std::endl;
    throw;
  }
  vsh.close();
  std::cerr << "DONE READING VERTEX SHADER\n";
  std::filesystem::path fsh_path(std::string("shaders/frag.glsl"));
  std::ifstream fsh;
  fsh.open(fsh_path.c_str());
  if (fsh.is_open()) {
    std::cerr << "Reading fragment shader\n";
    std::string fshdr_contents;
    while (!fsh.eof()) {
      fshdr_contents += fsh.get();
    }
    fshdr = glFunctions->glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar *shdr_cstr = fshdr_contents.c_str();
    int sizes[] = { (int)fshdr_contents.length() - 1 };
    glFunctions->glShaderSource(fshdr, 1, &shdr_cstr, sizes);
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
  fsh.close();
  std::cerr << "DONE READING FRAGMENT SHADER\n";
}
void Renderer::init_puck(std::vector<float> &coords) {
  GLuint VAO;
  glFunctions->glGenVertexArrays(1, &VAO);
  glFunctions->glBindVertexArray(VAO);

  GLuint buffer;
  glFunctions->glGenBuffers(1, &buffer);
  glFunctions->glBindBuffer(GL_ARRAY_BUFFER, buffer);
  GLint location =
      glFunctions->glGetAttribLocation(programs.at(PUCK_IDX), "pos");
  switch (location) {
  case -1: {
    std::cerr << "glGetAttribLocation could not get 'pos' location"
              << std::endl;
    throw;
  } break;
  default: {
    glFunctions->glBufferData(GL_ARRAY_BUFFER, sizeof(float) * coords.size(),
                              coords.data(), GL_DYNAMIC_DRAW);
    glFunctions->glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE,
                                       sizeof(float) * 2, 0);
    glFunctions->glEnableVertexAttribArray(location);
    vaos.push_back(VAO);
    vbos.push_back(std::vector<GLuint>{buffer});
  }
  }
  GLint color_location =
      glFunctions->glGetUniformLocation(programs.at(PUCK_IDX), "color");
  if (color_location == -1) {
    std::cerr << "color location -1" << std::endl;
    throw;
  }
  glFunctions->glUniform4f(color_location, 0.0f, 0.0f, 0.0f, 1.0f);

  GLuint ebo;
  glFunctions->glGenBuffers(1, &ebo);
  glFunctions->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  ebos.push_back(std::vector<GLuint>{ebo});

  std::array<int, NUM_SIDES * 3> vertices{{}};
  int counter = 0;
  for (int i = 0; i < (int)vertices.size(); i += 3) {
    vertices[i] = counter;
    vertices[i + 1] = counter + 1;
    vertices[i + 2] = NUM_VERTICES / 2 - 1;
    counter += 1;
  }
  glFunctions->glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                            sizeof(int) * vertices.size(), vertices.data(),
                            GL_STATIC_DRAW);
}
void Renderer::init_paddle(std::vector<float> &coords) {
  GLuint VAO;
  glFunctions->glGenVertexArrays(1, &VAO);
  glFunctions->glBindVertexArray(VAO);

  GLuint buffer;
  glFunctions->glGenBuffers(1, &buffer);
  glFunctions->glBindBuffer(GL_ARRAY_BUFFER, buffer);
  GLint location =
      glFunctions->glGetAttribLocation(programs.at(PADDLE_IDX), "pos");
  switch (location) {
  case -1: {
    std::cerr << "glGetAttribLocation could not get 'pos' location"
              << std::endl;
    throw;
  } break;
  default: {
    glFunctions->glBufferData(GL_ARRAY_BUFFER, sizeof(float) * coords.size(),
                              coords.data(), GL_DYNAMIC_DRAW);
    glFunctions->glVertexAttribPointer(location, 2, GL_FLOAT, false,
                                       sizeof(float) * 2, 0);
    glFunctions->glEnableVertexAttribArray(location);
    vaos.push_back(VAO);
    vbos.push_back(std::vector<GLuint>{buffer});
  }
  }
  GLint color_location =
      glFunctions->glGetUniformLocation(programs.at(PADDLE_IDX), "color");
  if (color_location == -1) {
    std::cerr << "color location -1" << std::endl;
    throw;
  }
  glFunctions->glUniform4f(color_location, 0.0f, 0.0f, 0.0f, 1.0f);

  GLuint ebo;
  glFunctions->glGenBuffers(1, &ebo);
  glFunctions->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  ebos.push_back(std::vector<GLuint>{ebo});

  std::array<int, NUM_SIDES * 3> vertices{{}};
  int counter = 0;
  for (int i = 0; i < (int)vertices.size(); i += 3) {
    vertices[i] = counter;
    vertices[i + 1] = counter + 1;
    vertices[i + 2] = NUM_VERTICES / 2 - 1;
    counter += 1;
  }
  glFunctions->glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                            sizeof(int) * vertices.size(), vertices.data(),
                            GL_STATIC_DRAW);
}
void Renderer::update_puck_inter_coords(std::vector<float> &coords) {
  glFunctions->glBindVertexArray(vaos.at(2));
  glFunctions->glBindBuffer(GL_ARRAY_BUFFER, vbos.at(2).at(0));
  glFunctions->glBufferSubData(GL_ARRAY_BUFFER, 0,
                               sizeof(float) * coords.size(), coords.data());
}
void Renderer::update_puck_coords(std::vector<float> &coords) {
  glFunctions->glBindVertexArray(vaos.at(PUCK_IDX));
  glFunctions->glBindBuffer(GL_ARRAY_BUFFER, vbos.at(PUCK_IDX).at(0));
  glFunctions->glBufferSubData(GL_ARRAY_BUFFER, 0,
                               sizeof(float) * coords.size(), coords.data());
}
void Renderer::update_paddle_coords(std::vector<float> &coords) {
  glFunctions->glBindVertexArray(vaos.at(PADDLE_IDX));
  glFunctions->glBindBuffer(GL_ARRAY_BUFFER, vbos.at(PADDLE_IDX).at(0));
  glFunctions->glBufferSubData(GL_ARRAY_BUFFER, 0,
                               sizeof(float) * coords.size(), coords.data());
}
void Renderer::load_assets() {
  std::filesystem::path texture_atlas_path(std::string("assets/puck->qoi"));
  SDL_RWops *src = SDL_RWFromFile(texture_atlas_path.c_str(), "rb");
  if (src == NULL) {
    std::cerr << SDL_GetError() << std::endl;
    throw;
  }
  texture_atlas = IMG_LoadQOI_RW(src);
}
Renderer::~Renderer() {
  SDL_DestroyWindow(window);
  SDL_Quit();
}
