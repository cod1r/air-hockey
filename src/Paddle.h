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
    float velocity_x = 0.0f;
    float velocity_y = 0.0f;
    float acceleration = 0.0f;
    std::array<float, NUM_VERTICES> vertices = generate_circle_verts(PADDLE_RADIUS);
    std::vector<float> vec;
};
#endif
