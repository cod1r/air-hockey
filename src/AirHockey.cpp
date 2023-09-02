#include "AirHockey.h"
#include "Renderer.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <format>
#include <filesystem>
AirHockey::AirHockey()
{
    renderer = new Renderer();
    std::vector<float> puck_coords(puck_vertices.begin(), puck_vertices.end());
    renderer->init_puck(puck_coords);
}
AirHockey::~AirHockey()
{
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
                    std::vector<float> puck_vec(puck_vertices.begin(), puck_vertices.end());
                    for (int i = 0; i < puck_vertices.size(); i += 2) {
                        puck_vec[i] += -(500 - e.motion.x) / 500.0f;
                        puck_vec[i + 1] += (500 - e.motion.y) / 500.0f;
                    }
                    renderer->update_puck_coords(puck_vec);
                } break;
            }
        }
        if (quit) break;
        renderer->render();
    }
}