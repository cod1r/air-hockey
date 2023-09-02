#include <SDL2/SDL.h>
#include <array>
#include <cmath>
#include <numbers>
#ifndef _AIR_HOCKEY_H
#define _AIR_HOCKEY_H
static const int NUM_SIDES = 32;
static const int NUM_VERTICES = (NUM_SIDES + 2) * 2;
constexpr std::array<float, NUM_VERTICES> generate_hexagon_vert()
{
    float radius = 0.2f;
    std::array<float, NUM_VERTICES> vertices{{}};
    for (size_t idx = 0; idx < NUM_VERTICES - 2; idx += 2) {
        float angle = (360.0f / NUM_SIDES) * (idx / 2) * std::numbers::pi / 180.0f;
        float x = std::cos(angle) * radius;
        float y = std::sin(angle) * radius;
        vertices[idx] = x;
        vertices[idx + 1] = y;
    }
    vertices[NUM_VERTICES - 2] = 0.0f;
    vertices[NUM_VERTICES - 1] = 0.0f;
    return vertices;
}
class Renderer;
class AirHockey {
public:
    Renderer *renderer = nullptr;
    std::array<float, NUM_VERTICES> puck_vertices = generate_hexagon_vert();
    AirHockey();
    ~AirHockey();
    void loop();
};
#endif