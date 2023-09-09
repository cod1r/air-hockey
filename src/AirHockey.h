#ifndef _AIR_HOCKEY_H
#define _AIR_HOCKEY_H
#include <SDL2/SDL.h>
#include <array>
#include <cmath>
#include <numbers>
class Puck;
class Paddle;
class Renderer;
static const int NUM_SIDES = 32;
static const int NUM_VERTICES = (NUM_SIDES + 2) * 2;
class AirHockey {
public:
    Puck *puck;
    Paddle *paddle;
    Renderer *renderer = nullptr;
    AirHockey();
    ~AirHockey();
    void loop();
};
#endif