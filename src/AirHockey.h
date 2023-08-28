#include <SDL2/SDL.h>
#ifndef _AIR_HOCKEY_H
#define _AIR_HOCKEY_H
class AirHockey {
    SDL_Window *window = nullptr;
public:
    AirHockey();
    ~AirHockey();
    void loop();
};
#endif