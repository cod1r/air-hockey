#include "AirHockey.h"
#include "Paddle.h"
#include "Puck.h"
#include "Renderer.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cassert>
#include <filesystem>
#include <format>
#include <iostream>
#include <numbers>
std::array<float, CONSTANTS::NUM_VERTICES> generate_circle_verts(float radius,
                                                      float offset) {
  std::array<float, CONSTANTS::NUM_VERTICES> vertices{{}};
  for (size_t idx = 0; idx < CONSTANTS::NUM_VERTICES - 2; idx += 2) {
    float angle = (360.0f / CONSTANTS::NUM_SIDES) * (idx / 2) * std::numbers::pi / 180.0f;
    float x = std::cos(angle) * radius;
    float y = std::sin(angle) * radius;
    vertices[idx] = x + offset;
    vertices[idx + 1] = y + offset;
  }
  vertices[CONSTANTS::NUM_VERTICES - 2] = 0.0f + offset;
  vertices[CONSTANTS::NUM_VERTICES - 1] = 0.0f + offset;
  return vertices;
}
AirHockey::AirHockey() {
  // puck_inter = new Puck();
  puck = new Puck();
  paddle = new Paddle();
  renderer = new Renderer();
  std::vector<float> puck_coords(puck->vertices.begin(), puck->vertices.end());
  renderer->init_puck(puck_coords);
  renderer->init_puck(puck_coords);
  std::vector<float> paddle_coords(paddle->vertices.begin(),
                                   paddle->vertices.end());
  renderer->init_paddle(paddle_coords);
}
AirHockey::~AirHockey() {}

void AirHockey::loop() {
  SDL_Event e;
  bool quit = false;
  bool flip = false;
  while (1) {
    bool mouse_ev = false;
    while (SDL_PollEvent(&e)) {
      switch (e.type) {
      case SDL_KEYDOWN: {
        switch (e.key.keysym.sym) {
        case SDLK_q: {
          quit = true;
        }
        case SDLK_s: {
          puck->velocity_x = 0.0f;
          puck->velocity_y = 0.0f;
          puck->vertices = generate_circle_verts(PUCK_RADIUS, 0.0f);
          puck->update();
        }
        }
      } break;
      case SDL_FINGERMOTION:
      case SDL_MOUSEMOTION: {
        std::cerr << e.motion.x << " " << e.motion.y << std::endl;
        paddle->update((e.motion.x - CONSTANTS::WINDOW_WIDTH) /
                           (float)CONSTANTS::WINDOW_WIDTH,
                       -(e.motion.y - CONSTANTS::WINDOW_HEIGHT) /
                           (float)CONSTANTS::WINDOW_HEIGHT);
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
    // paddle->update(flip ? -(250 - 500.0f)/500.0f : (250 - 500.0f)/500.0f,
    // flip ? -(750 - 500.0f)/ 500.0f : (750 - 500.0f) / 500.0f); flip = !flip;
    if (quit)
      break;
    if (!mouse_ev) {
      paddle->velocity_x = 0;
      paddle->velocity_y = 0;
    }
    puck->update();
    renderer->update_puck_coords(puck->vec);
    renderer->update_paddle_coords(paddle->vec);
    renderer->render();
  }
}
