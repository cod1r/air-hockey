#include <SDL2/SDL.h>
#ifndef _AIR_HOCKEY_H
#define _AIR_HOCKEY_H
class Renderer;
class AirHockey {
    SDL_Window *window = nullptr;
    Renderer *renderer = nullptr;
public:
    AirHockey();
    ~AirHockey();
    void load_assets();
    void loop();
};
#endif