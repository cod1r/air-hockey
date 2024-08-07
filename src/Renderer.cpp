#define QOI_IMPLEMENTATION
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
  window = SDL_CreateWindow("AirHockey", 0, 0, CONSTANTS::WINDOW_WIDTH,
                            CONSTANTS::WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
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
  glFunctions->glEnable(GL_TEXTURE_2D);
  read_shaders();
  {
    GLuint puck_program = glFunctions->glCreateProgram();
    glFunctions->glAttachShader(puck_program, vshdr);
    glFunctions->glAttachShader(puck_program, fshdr);
    glFunctions->glLinkProgram(puck_program);
    programs.push_back(puck_program);
  }
  {
    GLuint paddle_program = glFunctions->glCreateProgram();
    glFunctions->glAttachShader(paddle_program, vshdr);
    glFunctions->glAttachShader(paddle_program, fshdr);
    glFunctions->glLinkProgram(paddle_program);
    programs.push_back(paddle_program);
  }
  {
    GLuint texture_program = glFunctions->glCreateProgram();
    glFunctions->glAttachShader(texture_program, vshdr);
    glFunctions->glAttachShader(texture_program, fshdr);
    glFunctions->glLinkProgram(texture_program);
    programs.push_back(texture_program);
  }
  load_assets();
}
void Renderer::read_shaders() {
  std::cerr << "OPENGL VERSION: " << glFunctions->glGetString(GL_VERSION)
            << std::endl;
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
    int sizes[] = {(int)vshdr_contents.length() - 1};
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
    int sizes[] = {(int)fshdr_contents.length() - 1};
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
void Renderer::render() {
  glFunctions->glClear(GL_COLOR_BUFFER_BIT);
  glFunctions->glClearColor(1, 1, 1, 1);

  // glFunctions->glBindBuffer(GL_ARRAY_BUFFER, vbos.at(PUCK_IDX));
  // glFunctions->glVertexAttribPointer(buffer_info.at(PUCK_IDX).attrib_location,
  //                                    2, GL_FLOAT, GL_FALSE, sizeof(float) *
  //                                    2, 0);
  // glFunctions->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebos.at(PUCK_IDX));
  // glFunctions->glDrawElements(GL_TRIANGLES, CONSTANTS::NUM_SIDES * 3,
  //                             GL_UNSIGNED_INT, 0);

  // glFunctions->glBindBuffer(GL_ARRAY_BUFFER, vbos.at(PADDLE_IDX));
  // glFunctions->glVertexAttribPointer(buffer_info.at(PADDLE_IDX).attrib_location,
  //                                    2, GL_FLOAT, GL_FALSE, sizeof(float) *
  //                                    2, 0);
  // glFunctions->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebos.at(PADDLE_IDX));
  // glFunctions->glDrawElements(GL_TRIANGLES, CONSTANTS::NUM_SIDES * 3,
  //                             GL_UNSIGNED_INT, 0);
  glFunctions->glActiveTexture(GL_TEXTURE0);
  glFunctions->glBindTexture(GL_TEXTURE_2D, textures.at(0));

  glFunctions->glUseProgram(programs.at(2));
  glFunctions->glBindBuffer(GL_ARRAY_BUFFER, vbos.at(0));
  glFunctions->glVertexAttribPointer(buffer_info.at(0).attrib_location, 2,
                                     GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
  glFunctions->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebos.at(0));
  glFunctions->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  SDL_GL_SwapWindow(window);
}
void Renderer::init_test_texture() {
  GLuint texture_buffer;
  glFunctions->glGenBuffers(1, &texture_buffer);
  glFunctions->glBindBuffer(GL_ARRAY_BUFFER, texture_buffer);
  vbos.push_back(texture_buffer);

  float vertices[] = {
      0.5f, 0.5f, 0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f,
  };
  glFunctions->glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, vertices,
                            GL_STATIC_DRAW);
  GLuint ebo;
  glFunctions->glGenBuffers(1, &ebo);
  glFunctions->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

  int indices[] = {0, 1, 3, 1, 2, 3};

  glFunctions->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * 6, indices,
                            GL_STATIC_DRAW);
  ebos.push_back(ebo);

  GLint location = glFunctions->glGetAttribLocation(programs.at(2), "pos");
  switch (location) {
  case -1: {
    throw std::runtime_error("glGetAttribLocation could not get 'pos' location");
  } break;
  default: {
    glFunctions->glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE,
                                       sizeof(float) * 2, 0);
    glFunctions->glEnableVertexAttribArray(location);
    buffer_info.push_back({location});
  }
  }

  GLuint texture_buffer_coords;
  glFunctions->glGenBuffers(1, &texture_buffer_coords);
  glFunctions->glBindBuffer(GL_ARRAY_BUFFER, texture_buffer_coords);

      float tex_coords[] = {
        1.0f, 1.0f, 1.0f, 0.0f,  0.0f,  0.0f,  0.0f,  1.0f,
      };
  glFunctions->glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, tex_coords,
                            GL_STATIC_DRAW);
  GLint location_texture =
      glFunctions->glGetAttribLocation(programs.at(2), "in_tex_coord_t");
  switch (location_texture) {
  case -1: {
    throw std::runtime_error("glGetAttribLocation could not get 'in_tex_coord' location");
  } break;
  default: {
    glFunctions->glVertexAttribPointer(location_texture, 2, GL_FLOAT, GL_FALSE,
                                       sizeof(float) * 2,
                                       0);
    glFunctions->glEnableVertexAttribArray(location_texture);
    buffer_info.push_back({location_texture});
  }
  }
  GLuint texture;
  glFunctions->glGenTextures(1, &texture);
  glFunctions->glBindTexture(GL_TEXTURE_2D, texture);
  glFunctions->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
  glFunctions->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glFunctions->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glFunctions->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glFunctions->glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
  textures.push_back(texture);
  glFunctions->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, desc.width, desc.height,
                            0, GL_RGB, GL_UNSIGNED_BYTE, rgb_pixels);
  GLint sampler_location = glFunctions->glGetUniformLocation(programs.at(2), "sampler");
  if (sampler_location == -1) {
    throw std::runtime_error("sampler location is -1");
  }
  glFunctions->glUseProgram(programs.at(2));
  glFunctions->glUniform1i(sampler_location, 0);
}
void Renderer::init_puck(std::vector<float> &coords) {
  {
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
      glFunctions->glBufferData(GL_ARRAY_BUFFER,
                                sizeof(float) * CONSTANTS::NUM_VERTICES,
                                coords.data(), GL_DYNAMIC_DRAW);
      glFunctions->glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE,
                                         sizeof(float) * 2, 0);
      glFunctions->glEnableVertexAttribArray(location);
      buffer_info.push_back({location});
      vbos.push_back(buffer);
    }
    }
    glFunctions->glUseProgram(programs.at(PUCK_IDX));
    GLint color_location =
        glFunctions->glGetUniformLocation(programs.at(PUCK_IDX), "color");
    if (color_location == -1) {
      std::cerr << "color location -1" << std::endl;
      throw;
    }
    glFunctions->glUniform4f(color_location, 0, 0, 0, 1);
  }

  {
    GLuint ebo;
    glFunctions->glGenBuffers(1, &ebo);
    glFunctions->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    ebos.push_back(ebo);

    std::array<int, CONSTANTS::NUM_SIDES * 3> vertices{{}};
    int counter = 0;
    for (int i = 0; i < (int)vertices.size(); i += 3) {
      vertices[i] = counter;
      vertices[i + 1] = counter + 1;
      vertices[i + 2] = CONSTANTS::NUM_VERTICES / 2 - 1;
      counter += 1;
    }
    glFunctions->glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                              sizeof(int) * vertices.size(), vertices.data(),
                              GL_STATIC_DRAW);
  }
}
void Renderer::init_paddle(std::vector<float> &coords) {
  {
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
      glFunctions->glBufferData(GL_ARRAY_BUFFER,
                                sizeof(float) * CONSTANTS::NUM_VERTICES,
                                coords.data(), GL_DYNAMIC_DRAW);
      glFunctions->glVertexAttribPointer(location, 2, GL_FLOAT, false,
                                         sizeof(float) * 2, 0);
      glFunctions->glEnableVertexAttribArray(location);
      buffer_info.push_back({location});
      vbos.push_back(buffer);
    }
    }
    glFunctions->glUseProgram(programs.at(PADDLE_IDX));
    GLint color_location =
        glFunctions->glGetUniformLocation(programs.at(PADDLE_IDX), "color");
    if (color_location == -1) {
      std::cerr << "color location -1" << std::endl;
      throw;
    }
    glFunctions->glUniform4f(color_location, 0, 0, 0, 1);
  }

  {
    GLuint ebo;
    glFunctions->glGenBuffers(1, &ebo);
    glFunctions->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    ebos.push_back(ebo);

    std::array<int, CONSTANTS::NUM_SIDES * 3> vertices{{}};
    int counter = 0;
    for (int i = 0; i < (int)vertices.size(); i += 3) {
      vertices[i] = counter;
      vertices[i + 1] = counter + 1;
      vertices[i + 2] = CONSTANTS::NUM_VERTICES / 2 - 1;
      counter += 1;
    }
    glFunctions->glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                              sizeof(int) * vertices.size(), vertices.data(),
                              GL_STATIC_DRAW);
  }
}
void Renderer::update_puck_coords(std::vector<float> &coords) {
  glFunctions->glBindBuffer(GL_ARRAY_BUFFER, vbos.at(PUCK_IDX));
  glFunctions->glBufferSubData(GL_ARRAY_BUFFER, 0,
                               sizeof(float) * coords.size(), coords.data());
}
void Renderer::update_paddle_coords(std::vector<float> &coords) {
  glFunctions->glBindBuffer(GL_ARRAY_BUFFER, vbos.at(PADDLE_IDX));
  glFunctions->glBufferSubData(GL_ARRAY_BUFFER, 0,
                               sizeof(float) * coords.size(), coords.data());
}
void Renderer::load_assets() {
  rgb_pixels = (uint8_t *)qoi_read("assets/texture_atlas.qoi", &desc, 3);
  std::cerr << desc.width << " " << desc.height << std::endl;
  if (rgb_pixels == NULL) {
    std::cerr << "cannot read assets\n";
    throw;
  }
}
Renderer::~Renderer() {
  SDL_DestroyWindow(window);
  SDL_Quit();
}
