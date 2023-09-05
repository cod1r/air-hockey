#include <SDL2/SDL.h>
#include <array>
#include <cmath>
#include <numbers>
#ifndef _AIR_HOCKEY_H
#define _AIR_HOCKEY_H
static const int NUM_SIDES = 32;
static const int NUM_VERTICES = (NUM_SIDES + 2) * 2;
static const float PUCK_RADIUS = 0.02f;
static const float PADDLE_RADIUS = 0.02f * 1.625f;
std::array<float, NUM_VERTICES> generate_circle_verts(float radius);
class Renderer;
class AirHockey {
public:
    Renderer *renderer = nullptr;
    std::array<float, NUM_VERTICES> puck_vertices = generate_circle_verts(PUCK_RADIUS);
    std::array<float, NUM_VERTICES> paddle_vertices = generate_circle_verts(PADDLE_RADIUS);
    AirHockey();
    ~AirHockey();
    void loop();
};
#endif