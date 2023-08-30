#include "AirHockey.h"
#include "Renderer.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <format>
#include <filesystem>
AirHockey::AirHockey()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << SDL_GetError() << std::endl;
        throw;
    }
    window = SDL_CreateWindow("AirHockey", 0, 0, 600, 600, SDL_WINDOW_OPENGL);
    if (window == NULL) {
        std::cout << SDL_GetError() << std::endl;
        throw;
    }
    SDL_GLContext ctx = SDL_GL_CreateContext(window);
    if (SDL_GL_MakeCurrent(window, ctx) < 0) {
        std::cout << SDL_GetError() << std::endl;
        throw;
    }
    renderer = new Renderer();
}
AirHockey::~AirHockey()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void AirHockey::loop()
{
    SDL_Event e;
    bool quit = false;
    while (1) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_KEYDOWN: {
                    switch (e.key.keysym.sym) {
                        case SDLK_q: {
                            quit = true;
                        }
                    }
                } break;
                case SDL_FINGERMOTION:
                case SDL_MOUSEMOTION: {
                    std::cout << std::format("{} {}", e.motion.x, e.motion.y) << std::endl;
                } break;
            }
        }
        if (quit) break;
        renderer->render();
        SDL_GL_SwapWindow(window);
    }
}
void AirHockey::load_assets()
{
    std::filesystem::path texture_atlas(std::string("assets/puck.qoi"));
    SDL_RWops *src = SDL_RWFromFile(texture_atlas.c_str(), "rb");
    SDL_Surface *s = IMG_LoadQOI_RW(src);
}