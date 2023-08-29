#include "AirHockey.h"
#include "Renderer.h"
#include <SDL2/SDL.h>
#include <iostream>
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
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_q: {
                        quit = true;
                    }
                }
            }
        }
        if (quit) break;
        renderer->render();
        SDL_GL_SwapWindow(window);
    }
}