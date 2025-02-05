#include <OpenGL/gl.h>
#include <string_view>
#define QOI_IMPLEMENTATION
#include "Renderer.h"
#include "AirHockey.h"
#include "constants.h"
#include <SDL2/SDL_image.h>
#include <array>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <fmt/format.h>

Renderer::Renderer() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    throw std::runtime_error(SDL_GetError());
  }
  window = SDL_CreateWindow("AirHockey", 0, 0, CONSTANTS::WINDOW_WIDTH,
                            CONSTANTS::WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
  if (window == NULL) {
    throw std::runtime_error(SDL_GetError());
  }
  SDL_GLContext ctx = SDL_GL_CreateContext(window);
  if (SDL_GL_MakeCurrent(window, ctx) < 0) {
    throw std::runtime_error(SDL_GetError());
  }
  glEnable(GL_TEXTURE_2D);
  read_shaders();
  {
    GLuint puck_program = glCreateProgram();
    glAttachShader(puck_program, vshdr);
    glAttachShader(puck_program, fshdr);
    glLinkProgram(puck_program);
    programs.push_back(puck_program);
  }
  {
    GLuint paddle_program = glCreateProgram();
    glAttachShader(paddle_program, vshdr);
    glAttachShader(paddle_program, fshdr);
    glLinkProgram(paddle_program);
    programs.push_back(paddle_program);
  }
  {
    GLuint texture_program = glCreateProgram();
    glAttachShader(texture_program, vshdr);
    glAttachShader(texture_program, fshdr);
    glLinkProgram(texture_program);
    programs.push_back(texture_program);
  }
  load_assets();
}
void Renderer::read_shaders() {
  fmt::println("OPENGL VERSION: {}",
    std::string_view(reinterpret_cast<const char*>(glGetString(GL_VERSION))));
  fmt::println("SUPPORTS GL_TEXTURE_2D: {}", glIsEnabled(GL_TEXTURE_2D));
  std::filesystem::path vsh_path(std::string("shaders/vtx.glsl"));
  std::ifstream vsh;
  vsh.open(vsh_path.c_str());
  if (vsh.is_open()) {
    fmt::println(stderr, "Reading vertex shader");
    std::string vshdr_contents;
    while (!vsh.eof()) {
      vshdr_contents += vsh.get();
    }
    vshdr = glCreateShader(GL_VERTEX_SHADER);
    const GLchar *shdr_cstr = vshdr_contents.c_str();
    int sizes[] = {(int)vshdr_contents.length() - 1};
    glShaderSource(vshdr, 1, &shdr_cstr, sizes);
    glCompileShader(vshdr);
    GLint status;
    glGetShaderiv(vshdr, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
      GLsizei length;
      GLchar buffer[1024];
      glGetShaderInfoLog(vshdr, 1024, &length, buffer);
      fmt::println(stderr, "{}", buffer);
      throw;
    }
  } else {
    throw std::runtime_error("vertex shader could not be opened");
  }
  vsh.close();
  std::filesystem::path fsh_path(std::string("shaders/frag.glsl"));
  std::ifstream fsh;
  fsh.open(fsh_path.c_str());
  if (fsh.is_open()) {
    fmt::println(stderr, "Reading fragment shader");
    std::string fshdr_contents;
    while (!fsh.eof()) {
      fshdr_contents += fsh.get();
    }
    fshdr = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar *shdr_cstr = fshdr_contents.c_str();
    int sizes[] = {(int)fshdr_contents.length() - 1};
    glShaderSource(fshdr, 1, &shdr_cstr, sizes);
    glCompileShader(fshdr);
    GLint status;
    glGetShaderiv(fshdr, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
      GLsizei length;
      GLchar buffer[1024];
      glGetShaderInfoLog(fshdr, 1024, &length, buffer);
      fmt::println(stderr, "{}", buffer);
    }
  } else {
    throw std::runtime_error("fragment shader could not be opened");
  }
  fsh.close();
}
void Renderer::render() {
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(1, 1, 1, 1);
  {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures.at(0));

    glUseProgram(programs.at(TEXTURE_IDX));
    glBindBuffer(GL_ARRAY_BUFFER, vbos.at(TEXTURE_IDX));
    glVertexAttribPointer(buffer_info.at(TEXTURE_IDX).attrib_location, 2,
                          GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebos.at(TEXTURE_IDX));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }
  {
    glUseProgram(programs.at(PUCK_IDX));
    glBindBuffer(GL_ARRAY_BUFFER, vbos.at(PUCK_IDX));
    glVertexAttribPointer(buffer_info.at(PUCK_IDX).attrib_location,
                          2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebos.at(PUCK_IDX));
    glDrawElements(GL_TRIANGLES, CONSTANTS::NUM_SIDES * 3,
                                GL_UNSIGNED_INT, 0);
  }
  {
    glUseProgram(programs.at(PADDLE_IDX));
    glBindBuffer(GL_ARRAY_BUFFER, vbos.at(PADDLE_IDX));
    glVertexAttribPointer(buffer_info.at(PADDLE_IDX).attrib_location,
                          2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebos.at(PADDLE_IDX));
    glDrawElements(GL_TRIANGLES, CONSTANTS::NUM_SIDES * 3,
                                GL_UNSIGNED_INT, 0);
  }
  SDL_GL_SwapWindow(window);
}
void Renderer::init_table_texture() {
  GLuint texture_buffer;
  glGenBuffers(1, &texture_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, texture_buffer);
  vbos.push_back(texture_buffer);

  float vertices[] = {
      1.f, 1.f,
      1.f, -1.f,
      -1.f, -1.f,
      -1.f, 1.f,
  };
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, vertices,
                            GL_STATIC_DRAW);
  GLuint ebo;
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

  int indices[] = {0, 1, 3, 1, 2, 3};

  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * 6, indices,
                            GL_STATIC_DRAW);
  ebos.push_back(ebo);

  GLint location = glGetAttribLocation(programs.at(2), "pos");
  switch (location) {
  case -1: {
    throw std::runtime_error("glGetAttribLocation could not get 'pos' location");
  } break;
  default: {
    glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE,
                          sizeof(float) * 2, 0);
    glEnableVertexAttribArray(location);
    buffer_info.push_back({location});
  }
  }

  GLuint texture_buffer_coords;
  glGenBuffers(1, &texture_buffer_coords);
  glBindBuffer(GL_ARRAY_BUFFER, texture_buffer_coords);

  float tex_coords[] = {
    1.f, 1.f,
    1.f, 0.f,
    0.f, 0.f,
    0.f, 1.f,
  };
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, tex_coords,
                            GL_STATIC_DRAW);
  GLint location_texture =
      glGetAttribLocation(programs.at(2), "in_tex_coord_t");
  switch (location_texture) {
  case -1: {
    throw std::runtime_error("glGetAttribLocation could not get 'in_tex_coord' location");
  } break;
  default: {
    glVertexAttribPointer(location_texture, 2, GL_FLOAT, GL_FALSE,
                                       sizeof(float) * 2, 0);
    glEnableVertexAttribArray(location_texture);
    buffer_info.push_back({location_texture});
  }
  }
  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
  textures.push_back(texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, desc.width, desc.height,
                            0, GL_RGBA, GL_UNSIGNED_BYTE, rgb_pixels);
  GLint sampler_location = glGetUniformLocation(programs.at(2), "sampler");
  if (sampler_location == -1) {
    throw std::runtime_error("sampler location is -1");
  }
  glUseProgram(programs.at(TEXTURE_IDX));
  glUniform1i(sampler_location, 0);

    GLint no_texture_location =
        glGetUniformLocation(programs.at(TEXTURE_IDX), "no_texture");

    if (no_texture_location == -1) {
      fmt::println(stderr, "no_texture_location -1");
      throw;
    }

    glUniform1i(no_texture_location, 0);
}
void Renderer::init_puck(std::vector<float> &coords) {
  {
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    GLint location =
        glGetAttribLocation(programs.at(PUCK_IDX), "pos");
    switch (location) {
    case -1: {
      std::cerr << "glGetAttribLocation could not get 'pos' location"
                << std::endl;
      throw;
    } break;
    default: {
      glBufferData(GL_ARRAY_BUFFER,
                   sizeof(float) * CONSTANTS::NUM_VERTICES,
                   coords.data(), GL_DYNAMIC_DRAW);
      glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE,
                            sizeof(float) * 2, 0);
      glEnableVertexAttribArray(location);
      buffer_info.push_back({location});
      vbos.push_back(buffer);
    }
    }
    glUseProgram(programs.at(PUCK_IDX));
    GLint color_location =
        glGetUniformLocation(programs.at(PUCK_IDX), "color");
    if (color_location == -1) {
      fmt::println(stderr, "color location -1");
      throw;
    }
    glUniform4f(color_location, 0, 0, 0, 1);

    GLint no_texture_location =
        glGetUniformLocation(programs.at(PUCK_IDX), "no_texture");

    if (no_texture_location == -1) {
      fmt::println(stderr, "no_texture_location -1");
      throw;
    }

    glUniform1i(no_texture_location, 1);
  }

  {
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    ebos.push_back(ebo);

    std::array<int, CONSTANTS::NUM_SIDES * 3> vertices{{}};
    int counter = 0;
    for (size_t i = 0; i < vertices.size(); i += 3) {
      vertices[i] = counter;
      vertices[i + 1] = counter + 1;
      vertices[i + 2] = CONSTANTS::NUM_VERTICES / 2 - 1;
      counter += 1;
    }
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                              sizeof(int) * vertices.size(), vertices.data(),
                              GL_STATIC_DRAW);
  }
}
void Renderer::init_paddle(std::vector<float> &coords) {
  {
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    GLint location =
        glGetAttribLocation(programs.at(PADDLE_IDX), "pos");
    switch (location) {
    case -1: {
      std::cerr << "glGetAttribLocation could not get 'pos' location"
                << std::endl;
      throw;
    } break;
    default: {
      glBufferData(GL_ARRAY_BUFFER,
                   sizeof(float) * CONSTANTS::NUM_VERTICES,
                   coords.data(), GL_DYNAMIC_DRAW);
      glVertexAttribPointer(location, 2, GL_FLOAT, false,
                            sizeof(float) * 2, 0);
      glEnableVertexAttribArray(location);
      buffer_info.push_back({location});
      vbos.push_back(buffer);
    }
    }
    glUseProgram(programs.at(PADDLE_IDX));
    GLint color_location =
        glGetUniformLocation(programs.at(PADDLE_IDX), "color");
    if (color_location == -1) {
      std::cerr << "color location -1" << std::endl;
      throw;
    }
    glUniform4f(color_location, 0, 0, 0, 1);

    GLint no_texture_location =
        glGetUniformLocation(programs.at(PADDLE_IDX), "no_texture");

    if (no_texture_location == -1) {
      fmt::println(stderr, "no_texture_location -1");
      throw;
    }

    glUniform1i(no_texture_location, 1);
  }

  {
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    ebos.push_back(ebo);

    std::array<int, CONSTANTS::NUM_SIDES * 3> vertices{{}};
    int counter = 0;
    for (size_t i = 0; i < vertices.size(); i += 3) {
      vertices[i] = counter;
      vertices[i + 1] = counter + 1;
      vertices[i + 2] = CONSTANTS::NUM_VERTICES / 2 - 1;
      counter += 1;
    }
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                              sizeof(int) * vertices.size(), vertices.data(),
                              GL_STATIC_DRAW);
  }
}
void Renderer::update_puck_coords(const std::array<float, CONSTANTS::NUM_VERTICES> &coords) {
  auto x_scaled = coords;
  for (size_t i = 0; i < coords.size(); i += 2) x_scaled[i] = coords[i] * CONSTANTS::WINDOW_HEIGHT / CONSTANTS::WINDOW_WIDTH;
  glBindBuffer(GL_ARRAY_BUFFER, vbos.at(PUCK_IDX));
  glBufferSubData(GL_ARRAY_BUFFER, 0,
                               sizeof(float) * x_scaled.size(), x_scaled.data());
}
void Renderer::update_paddle_coords(const std::array<float, CONSTANTS::NUM_VERTICES> &coords) {
  auto x_scaled = coords;
  for (size_t i = 0; i < coords.size(); i += 2) x_scaled[i] = coords[i] * CONSTANTS::WINDOW_HEIGHT / CONSTANTS::WINDOW_WIDTH;
  glBindBuffer(GL_ARRAY_BUFFER, vbos.at(PADDLE_IDX));
  glBufferSubData(GL_ARRAY_BUFFER, 0,
                               sizeof(float) * x_scaled.size(), x_scaled.data());
}
void Renderer::load_assets() {
  rgb_pixels = (uint8_t *)qoi_read("assets/texture_atlas.qoi", &desc, 4);
  fmt::println("width: {}, height: {}", desc.width, desc.height);
  if (rgb_pixels == NULL) {
    throw std::runtime_error("cannot read assets");
  }
}
Renderer::~Renderer() {
  SDL_DestroyWindow(window);
  SDL_Quit();
}
