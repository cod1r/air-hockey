#ifndef _PUCK_H
#define _PUCK_H
#include <array>
#include <vector>
#include "constants.h"
static const float PUCK_MASS = 1.0f;
static const float PUCK_RADIUS = 0.02f;
class Puck {
    public:
    Puck();
    ~Puck();
    float facing_angle_radians;
    float velocity_x;
    float velocity_y;
    float acceleration;
    std::array<float, NUM_VERTICES> vertices = generate_circle_verts(PUCK_RADIUS, 0.0f);
    std::vector<float> vec;
    void update();
};
#endif
