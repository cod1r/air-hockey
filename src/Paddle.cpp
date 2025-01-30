#include "Paddle.h"
#include "AirHockey.h"
#include <fmt/format.h>

Paddle::Paddle() {
  vertices = generate_circle_verts(PADDLE_RADIUS, 0.0f, -0.5f);
}

void Paddle::update() {
  float most_add_x = velocity_x;
  float most_add_y = velocity_y;
  for (int i = 0; i < (int)vertices.size(); i += 2) {
    const auto x = vertices[i];
    const auto y = vertices[i + 1];
    if (velocity_x < 0.f && velocity_x + x < -1.f) {
      most_add_x = std::max(most_add_x, -1.f - x);
    }
    if (velocity_x > 0.f && velocity_x + x > 1.f) {
      most_add_x = std::min(most_add_x, 1.f - x);
    }
    if (velocity_y < 0.f && velocity_y + y < -1.f) {
      most_add_y = std::max(most_add_y, -1.f - y);
    }
    if (velocity_y > 0.f && velocity_y + y > 1.f) {
      most_add_y = std::min(most_add_y, 1.f - y);
    }
  }
  for (int i = 0; i < (int)vertices.size(); i += 2) {
    vertices[i] += most_add_x;
    vertices[i + 1] += most_add_y;
  }
}
