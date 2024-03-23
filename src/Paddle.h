#ifndef _PADDLE_H
#define _PADDLE_H
#include <array>
#include <vector>
#include "constants.h"
static const float PADDLE_MASS = 2.0f;
static const float PADDLE_RADIUS = 0.02f * 1.625f;
class Paddle {
    public:
    Paddle();
    ~Paddle();
    float velocity_x;
    float velocity_y;
    float acceleration;
    std::array<float, NUM_VERTICES> vertices;
    std::vector<float> vec;
    void update(float, float);
};
#endif
