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
    std::vector<float> paddle_coords(paddle_vertices.begin(), paddle_vertices.end());
    renderer->init_paddle(paddle_coords);
}
AirHockey::~AirHockey()
{
}

void AirHockey::loop()
{
    SDL_Event e;
    bool quit = false;
    std::vector<float> paddle_vec(paddle_vertices.size());
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
                    for (int i = 0; i < paddle_vertices.size(); i += 2) {
                        paddle_vec[i] = paddle_vertices[i] -(500 - e.motion.x) / 500.0f;
                        paddle_vec[i + 1] = paddle_vertices[i + 1] + (500 - e.motion.y) / 500.0f;
                    }
                    renderer->update_paddle_coords(paddle_vec);
                } break;
            }
        }
        if (quit) break;
        renderer->render();
    }
}