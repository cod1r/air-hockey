#include "AirHockey.h"
#include "Paddle.h"
#include "Puck.h"
#include "Renderer.h"
#include "src/constants.h"
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

void AirHockey::determine_puck_velocity_when_collided(Puck* puck, const Paddle* paddle) {
  float current_center_x = paddle->vertices[paddle->vertices.size() - 2];
  float current_center_y = paddle->vertices[paddle->vertices.size() - 1];
  float puck_center_x = puck->vertices[puck->vertices.size() - 2];
  float puck_center_y = puck->vertices[puck->vertices.size() - 1];
  float dist_x = puck_center_x - current_center_x;
  float dist_y = puck_center_y - current_center_y;
  float dist_from_puck_to_paddle = std::sqrt(dist_x * dist_x + dist_y * dist_y);
  float total_velocity = std::sqrt(paddle->velocity_x * paddle->velocity_x + paddle->velocity_y * paddle->velocity_y);
  const float both_radii = PUCK_RADIUS + PADDLE_RADIUS;
  if (dist_from_puck_to_paddle <= both_radii) {
    float dist_inside = both_radii - dist_from_puck_to_paddle;
    if (puck_center_x == current_center_x) {
      puck->velocity_y = total_velocity;
      for (size_t i = 0; i < puck->vertices.size(); i += 2) {
        if (dist_y < 0.f) puck->vertices[i + 1] += -dist_inside;
        else puck->vertices[i + 1] += dist_inside;
      }
    } else {
      float cos = dist_x / dist_from_puck_to_paddle;
      float x_vel = cos * total_velocity;
      float sin = dist_y / dist_from_puck_to_paddle;
      float y_vel = sin * total_velocity;
      puck->velocity_x = x_vel;
      puck->velocity_y = y_vel;
      float offset_x = cos * dist_inside;
      float offset_y = sin * dist_inside;
      for (size_t i = 0; i < puck->vertices.size(); i += 2) {
        puck->vertices[i] += offset_x;
        puck->vertices[i + 1] += offset_y;
      }
    }
  }
}

void AirHockey::loop() {
  SDL_Event e;
  bool quit = false;
  float mouse_x = 0.0f;
  float mouse_y = 0.0f;
  while (1) {
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
                    (CONSTANTS::WINDOW_WIDTH / 2.0f) * CONSTANTS::WINDOW_WIDTH / CONSTANTS::WINDOW_HEIGHT;
          mouse_y = -(e.motion.y - CONSTANTS::WINDOW_HEIGHT / 2.0f) /
                    (CONSTANTS::WINDOW_HEIGHT / 2.0f);
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
    update_paddle();
    determine_puck_velocity_when_collided(puck, paddle);
    update_puck();
    renderer->update_puck_coords(puck->vertices);
    renderer->update_paddle_coords(paddle->vertices);
    renderer->render();
  }
}

void AirHockey::update_puck() {

  float add_amt_x = puck->velocity_x;
  float add_amt_y = puck->velocity_y;

  for (size_t i = 0; i < puck->vertices.size(); i += 2) {
    const auto newX = puck->vertices[i] + add_amt_x;
    const auto newY = puck->vertices[i + 1] + add_amt_y;
    if (newX < CONSTANTS::LEFT_BOUNDARY || newX > CONSTANTS::RIGHT_BOUNDARY) {
      add_amt_x = -add_amt_x;
    }
    if (newX <= CONSTANTS::TOP_LEFT_BOUNDARY_X && newY >= CONSTANTS::TOP_LEFT_BOUNDARY_Y) {
      switch (puck->r) {
        case Region::LEFT: {
          add_amt_y = -add_amt_y;
        } break;
        case Region::RIGHT: {
          // this case shouldn't be possible
        } break;
        case Region::MIDDLE: {
          add_amt_x = -add_amt_x;
        } break;
      }
    }
    if (newX >= CONSTANTS::TOP_RIGHT_BOUNDARY_X && newY >= CONSTANTS::TOP_RIGHT_BOUNDARY_Y) {
      switch (puck->r) {
        case Region::LEFT: {
          // this case shouldn't be possible
        } break;
        case Region::RIGHT: {
          add_amt_y = -add_amt_y;
        } break;
        case Region::MIDDLE: {
          add_amt_x = -add_amt_x;
        } break;
      }
    }
    if (newX <= CONSTANTS::BOTTOM_LEFT_BOUNDARY_X && newY <= CONSTANTS::BOTTOM_LEFT_BOUNDARY_Y) {
      switch (puck->r) {
        case Region::LEFT: {
          add_amt_y = -add_amt_y;
        } break;
        case Region::RIGHT: {
          // this case shouldn't be possible
        } break;
        case Region::MIDDLE: {
          add_amt_x = -add_amt_x;
        } break;
      }
    }
    if (newX >= CONSTANTS::BOTTOM_RIGHT_BOUNDARY_X && newY <= CONSTANTS::BOTTOM_RIGHT_BOUNDARY_Y) {
      switch (puck->r) {
        case Region::LEFT: {
          // this case shouldn't be possible
        } break;
        case Region::RIGHT: {
          add_amt_y = -add_amt_y;
        } break;
        case Region::MIDDLE: {
          add_amt_x = -add_amt_x;
        } break;
      }
    }
  }
  float shift_vertical_amt = 0.f;
  float shift_horizontal_amt = 0.f;
  for (size_t i = 0; i < puck->vertices.size(); i += 2) {
    if (puck->vertices[i] < CONSTANTS::LEFT_BOUNDARY) {
      shift_horizontal_amt = std::max(CONSTANTS::LEFT_BOUNDARY - puck->vertices[i], shift_horizontal_amt);
    }
    if (puck->vertices[i] > CONSTANTS::RIGHT_BOUNDARY) {
      shift_horizontal_amt = std::min(CONSTANTS::RIGHT_BOUNDARY - puck->vertices[i], shift_horizontal_amt);
    }
    if (puck->vertices[i] >= CONSTANTS::BOTTOM_RIGHT_BOUNDARY_X && puck->vertices[i + 1] <= CONSTANTS::BOTTOM_RIGHT_BOUNDARY_Y) {
      switch (puck->r) {
        case Region::LEFT: {
          // this case shouldn't be possible
        } break;
        case Region::RIGHT: {
          shift_vertical_amt = std::max(CONSTANTS::BOTTOM_RIGHT_BOUNDARY_Y - puck->vertices[i + 1], shift_vertical_amt);
        } break;
        case Region::MIDDLE: {
          shift_horizontal_amt = std::min(CONSTANTS::BOTTOM_RIGHT_BOUNDARY_X - puck->vertices[i], shift_horizontal_amt);
        } break;
      }
    }
    if (puck->vertices[i] <= CONSTANTS::BOTTOM_LEFT_BOUNDARY_X && puck->vertices[i + 1] <= CONSTANTS::BOTTOM_LEFT_BOUNDARY_Y) {
      switch (puck->r) {
        case Region::LEFT: {
          shift_vertical_amt = std::max(CONSTANTS::BOTTOM_LEFT_BOUNDARY_Y - puck->vertices[i + 1], shift_vertical_amt);
        } break;
        case Region::RIGHT: {
          // this case shouldn't be possible
        } break;
        case Region::MIDDLE: {
          shift_horizontal_amt = std::max(CONSTANTS::BOTTOM_LEFT_BOUNDARY_X - puck->vertices[i], shift_horizontal_amt);
        } break;
      }
    }
    if (puck->vertices[i] >= CONSTANTS::TOP_RIGHT_BOUNDARY_X && puck->vertices[i + 1] >= CONSTANTS::TOP_RIGHT_BOUNDARY_Y) {
      switch (puck->r) {
        case Region::LEFT: {
          // this case shouldn't be possible
        } break;
        case Region::RIGHT: {
          shift_vertical_amt = std::min(CONSTANTS::TOP_RIGHT_BOUNDARY_Y - puck->vertices[i + 1], shift_vertical_amt);
        } break;
        case Region::MIDDLE: {
          shift_horizontal_amt = std::min(CONSTANTS::TOP_RIGHT_BOUNDARY_X - puck->vertices[i], shift_horizontal_amt);
        } break;
      }
    }
    if (puck->vertices[i] <= CONSTANTS::TOP_LEFT_BOUNDARY_X && puck->vertices[i + 1] >= CONSTANTS::TOP_LEFT_BOUNDARY_Y) {
      switch (puck->r) {
        case Region::LEFT: {
          shift_vertical_amt = std::min(CONSTANTS::TOP_LEFT_BOUNDARY_Y - puck->vertices[i + 1], shift_vertical_amt);
        } break;
        case Region::RIGHT: {
          // this case shouldn't be possible
        } break;
        case Region::MIDDLE: {
          shift_horizontal_amt = std::max(CONSTANTS::TOP_LEFT_BOUNDARY_X - puck->vertices[i], shift_horizontal_amt);
        } break;
      }
    }
  }
  for (size_t i = 0; i < puck->vertices.size(); i += 2) {
    puck->vertices[i] += add_amt_x;
    puck->vertices[i + 1] += add_amt_y;
    if (!std::isinf(shift_horizontal_amt)) {
      puck->vertices[i] += shift_horizontal_amt;
    }
    if (!std::isinf(shift_vertical_amt)) {
      puck->vertices[i + 1] += shift_vertical_amt;
    }
  }
  if (puck->vertices[puck->vertices.size() - 2] <= -0.18f) {
    puck->r = Region::LEFT;
  } else if (puck->vertices[puck->vertices.size() - 2] >= 0.18f) {
    puck->r = Region::RIGHT;
  } else {
    puck->r = Region::MIDDLE;
  }
  puck->velocity_x = add_amt_x * CONSTANTS::DECELERATION;
  puck->velocity_y = add_amt_y * CONSTANTS::DECELERATION;
}

bool AirHockey::is_puck_pinned() {
  if (puck->velocity_x < 0.f && puck->velocity_y > 0.f) {
    for (size_t i = 0; i < puck->vertices.size(); i += 2) {
      if (std::abs(puck->vertices[i] - CONSTANTS::LEFT_BOUNDARY) < 0.0001f &&
        std::abs(puck->vertices[i + 1] - CONSTANTS::TOP_LEFT_BOUNDARY_Y) < 0.0001f) {
        return true;
      }
    }
  } else if (puck->velocity_x > 0.f && puck->velocity_y > 0.f) {
    for (size_t i = 0; i < puck->vertices.size(); i += 2) {
      if (std::abs(puck->vertices[i] - CONSTANTS::RIGHT_BOUNDARY) < 0.0001f &&
        std::abs(puck->vertices[i + 1] - CONSTANTS::TOP_RIGHT_BOUNDARY_Y) < 0.0001f) {
        return true;
      }
    }
  } else if (puck->velocity_x < 0.f && puck->velocity_y < 0.f) {
    for (size_t i = 0; i < puck->vertices.size(); i += 2) {
      if (std::abs(puck->vertices[i] - CONSTANTS::LEFT_BOUNDARY) < 0.0001f &&
        std::abs(puck->vertices[i + 1] - CONSTANTS::BOTTOM_LEFT_BOUNDARY_Y) < 0.0001f) {
        return true;
      }
    }
  } else if (puck->velocity_x > 0.f && puck->velocity_y < 0.f) {
    for (size_t i = 0; i < puck->vertices.size(); i += 2) {
      if (std::abs(puck->vertices[i] - CONSTANTS::RIGHT_BOUNDARY) < 0.0001f &&
        std::abs(puck->vertices[i + 1] - CONSTANTS::BOTTOM_LEFT_BOUNDARY_Y) < 0.0001f) {
        return true;
      }
    }
  }
  return false;
}

void AirHockey::update_paddle() {
  if (is_puck_pinned()) return;
  for (size_t i = 0; i < paddle->vertices.size(); i += 2) {
    paddle->vertices[i] += paddle->velocity_x;
    paddle->vertices[i + 1] += paddle->velocity_y;
  }
}
