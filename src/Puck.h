#ifndef _PUCK_H
#define _PUCK_H
static const float PUCK_MASS = 1.0f;
static const float PUCK_RADIUS = 0.02f;
constexpr std::array<float, NUM_VERTICES> generate_circle_verts(float radius);
class Puck {
    public:
    Puck() = default;
    ~Puck();
    float puck_velocity = 0.0f;
    float puck_acceleration = 0.0f;
    std::array<float, NUM_VERTICES> puck_vertices = generate_circle_verts(PUCK_RADIUS);
};
#endif