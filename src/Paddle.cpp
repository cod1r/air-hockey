#include "Paddle.h"
#include "AirHockey.h"
#include <iostream>
#include <vector>

Paddle::Paddle() {
  vertices = generate_circle_verts(PADDLE_RADIUS, 0.0f, -0.5f);
  vec = std::vector<float>(vertices.begin(), vertices.end());
}

void Paddle::update(float new_x, float new_y) {
  for (int i = 0; i < (int)vertices.size(); i += 2) {
    if (vertices[i] + new_x < -1.0f || vertices[i] + new_x > 1.0f) {
      return;
    }
    if (vertices[i + 1] + new_y < -1.0f || vertices[i + 1] + new_y > 1.0f) {
      return;
    }
  }
  for (int i = 0; i < (int)vertices.size(); i += 2) {
    vertices[i] += new_x;
    vertices[i + 1] += new_y;
    vec[i] = vertices[i];
    vec[i + 1] = vertices[i + 1];
  }
}
