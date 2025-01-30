#include "Puck.h"
#include "AirHockey.h"

Puck::Puck() {
  vertices = generate_circle_verts(PUCK_RADIUS, 0.0f, 0.0f);
  velocity_x = 0.0f;
  velocity_y = 0.0f;
}

void Puck::update() {
  float add_amt_x = velocity_x;
  float add_amt_y = velocity_y;
  for (int i = 0; i < (int)vertices.size(); i += 2) {
    if (vertices[i] + add_amt_x < -1.0f || vertices[i] + add_amt_x > 1.0f) {
      add_amt_x = -add_amt_x;
    }
    if (vertices[i + 1] + add_amt_y < -1.0f ||
        vertices[i + 1] + add_amt_y > 1.0f) {
      add_amt_y = -add_amt_y;
    }
  }
  for (int i = 0; i < (int)vertices.size(); i += 2) {
    vertices[i] += add_amt_x;
    vertices[i + 1] += add_amt_y;
  }
  velocity_x = add_amt_x;
  velocity_y = add_amt_y;
}
