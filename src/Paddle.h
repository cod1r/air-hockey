#ifndef _PADDLE_H
#define _PADDLE_H
#include "constants.h"
#include <array>
static const float PADDLE_RADIUS = 0.05f;
class Paddle {
public:
  float velocity_x = 0;
  float velocity_y = 0;
  Paddle();
  ~Paddle();
  std::array<float, CONSTANTS::NUM_VERTICES> vertices;
};
#endif
