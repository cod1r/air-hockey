#include "AirHockey.h"
#include "Renderer.h"
#include "Paddle.h"
#include "Puck.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <format>
#include <filesystem>
AirHockey::AirHockey()
{
    puck = new Puck();
    paddle = new Paddle();
    renderer = new Renderer();
    std::vector<float> puck_coords(puck->vertices.begin(), puck->vertices.end());
    renderer->init_puck(puck_coords);
    std::vector<float> paddle_coords(paddle->vertices.begin(), paddle->vertices.end());
    renderer->init_paddle(paddle_coords);
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
                    for (int i = 0; i < paddle->vertices.size(); i += 2) {
                        paddle->vec[i] = paddle->vertices[i] -(500 - e.motion.x) / 500.0f;
                        paddle->vec[i + 1] = paddle->vertices[i + 1] + (500 - e.motion.y) / 500.0f;
                    }
                    bool collided = false;
                    for (int i = 0; i < puck->vertices.size() - 2; i += 2) {
                        float diff_x = std::pow(paddle->vec[i] - puck->vertices[puck->vertices.size() - 2], 2);
                        float diff_y = std::pow(paddle->vec[i + 1] - puck->vertices[puck->vertices.size() - 1], 2);
                        if (std::sqrt(diff_x + diff_y) <= PUCK_RADIUS) {
                            collided = true;
                            break;
                        }
                    }
                    if (collided) {
                        int index_of_closest = 0;
                        for (int idx = 0; idx < puck->vertices.size() - 2; idx += 2) {
                            float diff_x = std::pow(puck->vertices[puck->vertices.size() - 2] - paddle->vec[idx], 2);
                            float diff_y = std::pow(puck->vertices[puck->vertices.size() - 1] - paddle->vec[idx + 1], 2);
                            float dist_curr = std::sqrt(diff_x + diff_y);
                            float diff_xclosest = std::pow(puck->vertices[puck->vertices.size() - 2] - paddle->vec[index_of_closest], 2);
                            float diff_yclosest = std::pow(puck->vertices[puck->vertices.size() - 1] - paddle->vec[index_of_closest + 1], 2);
                            float dist_closest = std::sqrt(diff_xclosest + diff_yclosest);
                            if (dist_curr < dist_closest) {
                                index_of_closest = idx;
                            }
                        }
                        puck->velocity_x = -(500 - e.motion.x) / 500.0f;
                        puck->velocity_y = (500 - e.motion.y) / 500.0f;
                        puck->update();
                        renderer->update_puck_coords(puck->vec);
                    }
                    renderer->update_paddle_coords(paddle->vec);
                } break;
            }
        }
        if (quit) break;
        renderer->render();
    }
}
