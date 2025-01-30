#include "AirHockey.h"
#include "Paddle.h"
#include "Puck.h"
#include "Renderer.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>
#include <numbers>
#include <fmt/format.h>
std::array<float, CONSTANTS::NUM_VERTICES>
generate_circle_verts(float radius, float offsetx, float offsety) {
  std::array<float, CONSTANTS::NUM_VERTICES> vertices{{}};
  for (size_t idx = 0; idx < CONSTANTS::NUM_VERTICES - 2; idx += 2) {
    float angle =
        (360.0f / CONSTANTS::NUM_SIDES) * (static_cast<float>(idx) / 2.f) * static_cast<float>(std::numbers::pi) / 180.0f;
    float x = std::cos(angle) * radius;
    float y = std::sin(angle) * radius;
    vertices[idx] = x + offsetx;
    vertices[idx + 1] = y + offsety;
  }
  vertices[CONSTANTS::NUM_VERTICES - 2] = offsetx;
  vertices[CONSTANTS::NUM_VERTICES - 1] = offsety;
  return vertices;
}
AirHockey::AirHockey() {
  puck = new Puck();
  paddle = new Paddle();
  renderer = new Renderer();
  std::vector<float> puck_coords(puck->vertices.begin(), puck->vertices.end());
  std::vector<float> paddle_coords(paddle->vertices.begin(),
                                   paddle->vertices.end());
  renderer->init_puck(puck_coords);
  renderer->init_paddle(paddle_coords);
  renderer->init_table_texture();
}
AirHockey::~AirHockey() {}

void AirHockey::loop() {
  SDL_Event e;
  bool quit = false;
  float mouse_x = 0.0f;
  float mouse_y = 0.0f;
  while (1) {
    bool mouse_ev = false;
    while (SDL_PollEvent(&e)) {
      switch (e.type) {
      case SDL_KEYDOWN: {
        switch (e.key.keysym.sym) {
          case SDLK_q: {
            quit = true;
          }
        }
      } break;
      case SDL_FINGERMOTION:
      case SDL_MOUSEMOTION: {
        mouse_x = (e.motion.x - CONSTANTS::WINDOW_WIDTH / 2.0f) /
                  (CONSTANTS::WINDOW_WIDTH / 2.0f);
        mouse_y = -(e.motion.y - CONSTANTS::WINDOW_HEIGHT / 2.0f) /
                  (CONSTANTS::WINDOW_HEIGHT / 2.0f);
        mouse_ev = true;
      } break;
      case SDL_WINDOWEVENT: {
        switch (e.window.event) {
          case SDL_WINDOWEVENT_CLOSE: {
            quit = true;
          } break;
        }
      } break;
      }
    }
    if (quit)
      break;
    float current_center_x = paddle->vertices[paddle->vertices.size() - 2];
    float current_center_y = paddle->vertices[paddle->vertices.size() - 1];
    paddle->velocity_x = 0.002f * (mouse_x - current_center_x);
    paddle->velocity_y = 0.002f * (mouse_y - current_center_y);
    paddle->update();
    renderer->update_paddle_coords(paddle->vertices);
    /*puck->update();*/
    /*renderer->update_puck_coords(puck->vertices);*/
    renderer->render();
  }
}
