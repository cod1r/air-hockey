#include "Paddle.h"
#include "AirHockey.h"
#include <iostream>
#include <vector>

Paddle::Paddle() {
  vec = std::vector<float>(vertices.begin(), vertices.end());
  vertices = generate_circle_verts(PADDLE_RADIUS, 0.5f);
  velocity_x = 0.0f;
  velocity_y = 0.0f;
}

void Paddle::update(float new_x, float new_y) {
  float old_paddle_x = vec[vec.size() - 2];
  float old_paddle_y = vec[vec.size() - 1];
  for (int i = 0; i < (int)vertices.size(); i += 2) {
    vertices[i] += new_x - old_paddle_x;
    vertices[i + 1] += new_y - old_paddle_y;
    vec[i] = vertices[i];
    vec[i + 1] = vertices[i + 1];
  }
  velocity_x = vec[vec.size() - 2] - old_paddle_x;
  velocity_y = vec[vec.size() - 1] - old_paddle_y;
}
