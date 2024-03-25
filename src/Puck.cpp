#include "Puck.h"
#include "AirHockey.h"
#include <climits>
#include <iostream>
#include <vector>

Puck::Puck() {
  vertices = generate_circle_verts(PUCK_RADIUS, 0.0f, 0.0f);
  vec = std::vector<float>(vertices.begin(), vertices.end());
  velocity_x = 0.0f;
  velocity_y = 0.0f;
}

void Puck::update() {
  float add_amt_x = velocity_x;
  float add_amt_y = velocity_y;
  for (int i = 0; i < (int)vertices.size(); i += 2) {
    if (vertices[i] + velocity_x >= 1.0f) {
      add_amt_x = std::min(add_amt_x, 1.0f - (vertices[i] + PUCK_RADIUS));
      velocity_x = -velocity_x;
    } else if (vertices[i] + velocity_x <= -1.0f) {
      add_amt_x = std::min(add_amt_x, (-1.0f - (vertices[i] - PUCK_RADIUS)));
      velocity_x = -velocity_x;
    }
    if (vertices[i + 1] + velocity_y >= 1.0f) {
      add_amt_y = std::min(add_amt_y, 1.0f - (vertices[i + 1] + PUCK_RADIUS));
      velocity_y = -velocity_y;
    } else if (vertices[i + 1] + velocity_y <= -1.0f) {
      add_amt_y =
          std::min(add_amt_y, (-1.0f - (vertices[i + 1] - PUCK_RADIUS)));
      velocity_y = -velocity_y;
    }
  }
  for (int i = 0; i < (int)vertices.size(); i += 2) {
    vertices[i] += add_amt_x;
    vertices[i + 1] += add_amt_y;
    vec[i] = vertices[i];
    vec[i + 1] = vertices[i + 1];
  }
}
