#ifndef _PADDLE_H
#define _PADDLE_H
static const float PADDLE_MASS = 2.0f;
static const float PADDLE_RADIUS = 0.02f * 1.625f;
constexpr std::array<float, NUM_VERTICES> generate_circle_verts(float radius);
class Paddle {
    public:
    Paddle() = default;
    ~Paddle();
    float paddle_velocity = 0.0f;
    float paddle_acceleration = 0.0f;
    std::array<float, NUM_VERTICES> paddle_vertices = generate_circle_verts(PADDLE_RADIUS);
};
#endif