#ifndef _PUCK_H
#define _PUCK_H
#include "constants.h"
#include <array>
#include <vector>
static const float PUCK_RADIUS = 0.03f;
class Puck {
public:
  Puck();
  ~Puck();
  float velocity_x;
  float velocity_y;
  float acceleration;
  std::array<float, CONSTANTS::NUM_VERTICES> vertices;
  std::vector<float> vec;
  void update();
};
#endif
