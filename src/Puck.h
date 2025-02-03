#ifndef _PUCK_H
#define _PUCK_H
#include "constants.h"
#include <array>
static const float PUCK_RADIUS = 0.03f;
static const float MAX_SPEED = 100.f;
enum class Region {
  LEFT,
  MIDDLE,
  RIGHT
};
class Puck {
public:
  Puck();
  ~Puck();
  Region r = Region::MIDDLE;
  float velocity_x = 0;
  float velocity_y = 0;
  float acceleration;
  std::array<float, CONSTANTS::NUM_VERTICES> vertices;
};
#endif
