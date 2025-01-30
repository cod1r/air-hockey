#include "Paddle.h"
#include "AirHockey.h"
#include <fmt/format.h>

Paddle::Paddle() {
  vertices = generate_circle_verts(PADDLE_RADIUS, 0.0f, -0.5f);
}

void Paddle::update() {
  for (int i = 0; i < (int)vertices.size(); i += 2) {
    vertices[i] += velocity_x;
    vertices[i + 1] += velocity_y;
  }
}
