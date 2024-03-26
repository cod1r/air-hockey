#ifndef _PADDLE_H
#define _PADDLE_H
#include "constants.h"
#include <array>
#include <vector>
static const float PADDLE_RADIUS = 0.05f;
class Paddle {
public:
  Paddle();
  ~Paddle();
  std::array<float, CONSTANTS::NUM_VERTICES> vertices;
  std::vector<float> vec;
  void update(float, float);
};
#endif
