#ifndef _AIR_HOCKEY_H
#define _AIR_HOCKEY_H
#include <SDL2/SDL.h>
#include <array>
#include <cmath>
#include <numbers>
class Puck;
class Paddle;
class Renderer;
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
