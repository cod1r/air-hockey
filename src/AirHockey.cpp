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
std::array<float, NUM_VERTICES> generate_circle_verts(float radius,
                                                      float offset) {
  std::array<float, NUM_VERTICES> vertices{{}};
  for (size_t idx = 0; idx < NUM_VERTICES - 2; idx += 2) {
    float angle = (360.0f / NUM_SIDES) * (idx / 2) * std::numbers::pi / 180.0f;
    float x = std::cos(angle) * radius;
    float y = std::sin(angle) * radius;
    vertices[idx] = x + offset;
    vertices[idx + 1] = y + offset;
  }
  vertices[NUM_VERTICES - 2] = 0.0f + offset;
  vertices[NUM_VERTICES - 1] = 0.0f + offset;
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
        paddle->update((e.motion.x - 500.0f) / 500.0f,
                       -(e.motion.y - 500.0f) / 500.0f);
        mouse_ev = true;
      } break;
      }
    }
    // paddle->update(flip ? -(250 - 500.0f)/500.0f : (250 - 500.0f)/500.0f,
    // flip ? -(750 - 500.0f)/ 500.0f : (750 - 500.0f) / 500.0f); flip = !flip;
    if (quit)
      break;
    bool collided = false;
    float prev_y_paddle =
        paddle->vec[paddle->vec.size() - 1] - paddle->velocity_y;
    float prev_x_paddle =
        paddle->vec[paddle->vec.size() - 2] - paddle->velocity_x;
    float distance_between_two_centers =
        std::sqrt(std::pow(puck->vertices[puck->vertices.size() - 2] -
                               paddle->vec[paddle->vec.size() - 2],
                           2.0f) +
                  std::pow(puck->vertices[puck->vertices.size() - 1] -
                               paddle->vec[paddle->vec.size() - 1],
                           2.0f));
    float distance_between_old_paddle_and_puck = std::sqrt(
        std::pow(prev_x_paddle - puck->vertices[puck->vertices.size() - 2],
                 2.0f) +
        std::pow(prev_y_paddle - puck->vertices[puck->vertices.size() - 1],
                 2.0f));
    if ((((prev_x_paddle - PADDLE_RADIUS <=
               puck->vertices[puck->vertices.size() - 2] - PUCK_RADIUS &&
           puck->vertices[puck->vertices.size() - 2] + PUCK_RADIUS <=
               paddle->vec[paddle->vec.size() - 2] + PADDLE_RADIUS) ||
          (prev_x_paddle - PADDLE_RADIUS >=
               puck->vertices[puck->vertices.size() - 2] - PUCK_RADIUS &&
           puck->vertices[puck->vertices.size() - 2] + PUCK_RADIUS >=
               paddle->vec[paddle->vec.size() - 2] + PADDLE_RADIUS)) &&
         ((prev_y_paddle - PADDLE_RADIUS <=
               puck->vertices[puck->vertices.size() - 1] - PUCK_RADIUS &&
           puck->vertices[puck->vertices.size() - 1] + PUCK_RADIUS <=
               paddle->vec[paddle->vec.size() - 1] + PADDLE_RADIUS) ||
          (prev_y_paddle - PADDLE_RADIUS >=
               puck->vertices[puck->vertices.size() - 1] - PUCK_RADIUS &&
           puck->vertices[puck->vertices.size() - 1] + PUCK_RADIUS >=
               paddle->vec[paddle->vec.size() - 1] + PADDLE_RADIUS))) ||
        (distance_between_two_centers <= PUCK_RADIUS + PADDLE_RADIUS)) {
      std::cerr << paddle->velocity_y << " " << paddle->velocity_x << std::endl;
      if (puck->velocity_y != 0 && puck->velocity_x != 0 &&
          paddle->velocity_y != 0 && paddle->velocity_x != 0) {
      } else if (paddle->velocity_x != 0 || paddle->velocity_y != 0) {
        if (paddle->velocity_x == 0) {
          float x_diff = puck->vertices[puck->vertices.size() - 2] -
                         paddle->vec[paddle->vec.size() - 2];
          if (x_diff != 0.0f) {
            float b_length =
                std::sqrt(std::pow(PUCK_RADIUS + PADDLE_RADIUS, 2.0f) -
                          std::pow(x_diff, 2.0f));
            float y_collision_paddle =
                puck->vertices[puck->vertices.size() - 1] - b_length;
            float collide_slope =
                (puck->vertices[puck->vertices.size() - 1] -
                 y_collision_paddle) /
                (puck->vertices[puck->vertices.size() - 2] - prev_x_paddle);
            float magnitude = std::sqrt(std::pow(paddle->velocity_x, 2.0f) +
                                        std::pow(paddle->velocity_y, 2.0f));
            puck->velocity_x = std::cos(std::atan(collide_slope)) * magnitude;
            puck->velocity_y = std::sin(std::atan(collide_slope)) * magnitude;
            if ((puck->vertices[puck->vertices.size() - 2] < prev_x_paddle &&
                 puck->velocity_x > 0.0f) ||
                (puck->vertices[puck->vertices.size() - 2] > prev_x_paddle &&
                 puck->velocity_x < 0.0f)) {
              puck->velocity_x = -puck->velocity_x;
            }
            if ((puck->vertices[puck->vertices.size() - 1] < prev_y_paddle &&
                 puck->velocity_y > 0.0f) ||
                (puck->vertices[puck->vertices.size() - 1] > prev_y_paddle &&
                 puck->velocity_y < 0.0f)) {
              puck->velocity_y = -puck->velocity_y;
            }
          } else {
            throw "TODO";
          }
        } else if (paddle->velocity_y == 0) {
          float y_diff = puck->vertices[puck->vertices.size() - 1] -
                         paddle->vec[paddle->vec.size() - 1];
          if (y_diff != 0.0f) {
            float b_length =
                std::sqrt(std::pow(PUCK_RADIUS + PADDLE_RADIUS, 2.0f) -
                          std::pow(y_diff, 2.0f));
            float x_collision_paddle =
                puck->vertices[puck->vertices.size() - 2] - b_length;
            float collide_slope =
                (puck->vertices[puck->vertices.size() - 1] - prev_y_paddle) /
                (puck->vertices[puck->vertices.size() - 2] -
                 x_collision_paddle);
            float magnitude = std::sqrt(std::pow(paddle->velocity_x, 2.0f) +
                                        std::pow(paddle->velocity_y, 2.0f));
            puck->velocity_x = std::cos(std::atan(collide_slope)) * magnitude;
            puck->velocity_y = std::sin(std::atan(collide_slope)) * magnitude;
            if ((puck->vertices[puck->vertices.size() - 2] < prev_x_paddle &&
                 puck->velocity_x > 0.0f) ||
                (puck->vertices[puck->vertices.size() - 2] > prev_x_paddle &&
                 puck->velocity_x < 0.0f)) {
              puck->velocity_x = -puck->velocity_x;
            }
            if ((puck->vertices[puck->vertices.size() - 1] < prev_y_paddle &&
                 puck->velocity_y > 0.0f) ||
                (puck->vertices[puck->vertices.size() - 1] > prev_y_paddle &&
                 puck->velocity_y < 0.0f)) {
              puck->velocity_y = -puck->velocity_y;
            }
          } else {
            throw "TODO";
          }
        } else {
          float slope_paddle = paddle->velocity_y / paddle->velocity_x;
          float y_offset_paddle = prev_y_paddle - slope_paddle * prev_x_paddle;
          float perpendicular_slope = -paddle->velocity_x / paddle->velocity_y;
          float y_offset_puck =
              puck->vertices[puck->vertices.size() - 1] -
              perpendicular_slope * puck->vertices[puck->vertices.size() - 2];
          float x_intersection = (y_offset_puck - y_offset_paddle) /
                                 (slope_paddle - perpendicular_slope);
          float y_intersection =
              slope_paddle * x_intersection + y_offset_paddle;
          float length_1 =
              std::sqrt(std::pow(puck->vertices[puck->vertices.size() - 2] -
                                     x_intersection,
                                 2.0f) +
                        std::pow(puck->vertices[puck->vertices.size() - 1] -
                                     y_intersection,
                                 2.0f));
          if (std::sqrt(std::pow(x_intersection -
                                     puck->vertices[puck->vertices.size() - 2],
                                 2.0f) +
                        std::pow(y_intersection -
                                     puck->vertices[puck->vertices.size() - 1],
                                 2.0f)) <= PUCK_RADIUS + PADDLE_RADIUS) {
            float collision_paddle_y;
            float collision_paddle_x;
            if (length_1 > 0.0f) {
              float length_3 =
                  std::sqrt(std::pow(PUCK_RADIUS + PADDLE_RADIUS, 2.0f) -
                            std::pow(length_1, 2.0f));
              float length_x = std::cos(std::atan(slope_paddle)) * length_3;
              collision_paddle_x = x_intersection + length_x;
              collision_paddle_y =
                  slope_paddle * collision_paddle_x + y_offset_paddle;
            } else {
              float x_offset = std::cos(std::atan(slope_paddle)) *
                               (PUCK_RADIUS + PADDLE_RADIUS);
              collision_paddle_x =
                  puck->vertices[puck->vertices.size() - 2] + x_offset;
              collision_paddle_y =
                  slope_paddle * collision_paddle_x + y_offset_paddle;
            }
            float collide_slope = (collision_paddle_y -
                                   puck->vertices[puck->vertices.size() - 1]) /
                                  (collision_paddle_x -
                                   puck->vertices[puck->vertices.size() - 2]);
            float magnitude = std::sqrt(std::pow(paddle->velocity_x, 2.0f) +
                                        std::pow(paddle->velocity_y, 2.0f));
            puck->velocity_x = std::cos(std::atan(collide_slope)) * magnitude;
            puck->velocity_y = std::sin(std::atan(collide_slope)) * magnitude;
            if ((puck->vertices[puck->vertices.size() - 2] < prev_x_paddle &&
                 puck->velocity_x > 0.0f) ||
                (puck->vertices[puck->vertices.size() - 2] > prev_x_paddle &&
                 puck->velocity_x < 0.0f)) {
              puck->velocity_x = -puck->velocity_x;
            }
            if ((puck->vertices[puck->vertices.size() - 1] < prev_y_paddle &&
                 puck->velocity_y > 0.0f) ||
                (puck->vertices[puck->vertices.size() - 1] > prev_y_paddle &&
                 puck->velocity_y < 0.0f)) {
              puck->velocity_y = -puck->velocity_y;
            }
          }
        }
      } else if (puck->velocity_x != 0 || puck->velocity_y != 0) {
      }
    }
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
