#include "AirHockey.h"
#include "Renderer.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <format>
#include <filesystem>
std::array<float, NUM_VERTICES> generate_circle_verts(float radius)
{
    std::array<float, NUM_VERTICES> vertices{{}};
    for (size_t idx = 0; idx < NUM_VERTICES - 2; idx += 2) {
        float angle = (360.0f / NUM_SIDES) * (idx / 2) * std::numbers::pi / 180.0f;
        float x = std::cos(angle) * radius;
        float y = std::sin(angle) * radius;
        vertices[idx] = x;
        vertices[idx + 1] = y;
    }
    vertices[NUM_VERTICES - 2] = 0.0f;
    vertices[NUM_VERTICES - 1] = 0.0f;
    return vertices;
}
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
    std::vector<float> puck_vec(puck_vertices.size());
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
                    bool collided = false;
                    for (int i = 0; i < puck_vertices.size() - 2; i += 2) {
                        float diff_x = std::pow(paddle_vec[i] - puck_vertices[puck_vertices.size() - 2], 2);
                        float diff_y = std::pow(paddle_vec[i + 1] - puck_vertices[puck_vertices.size() - 1], 2);
                        if (std::sqrt(diff_x + diff_y) <= PUCK_RADIUS) {
                            collided = true;
                            break;
                        }
                    }
                    if (collided) {
                        int index_of_closest = 0;
                        for (int idx = 0; idx < puck_vertices.size() - 2; idx += 2) {
                            float diff_x = std::pow(puck_vertices[puck_vertices.size() - 2] - paddle_vec[idx], 2);
                            float diff_y = std::pow(puck_vertices[puck_vertices.size() - 1] - paddle_vec[idx + 1], 2);
                            float dist_curr = std::sqrt(diff_x + diff_y);
                            float diff_xclosest = std::pow(puck_vertices[puck_vertices.size() - 2] - paddle_vec[index_of_closest], 2);
                            float diff_yclosest = std::pow(puck_vertices[puck_vertices.size() - 1] - paddle_vec[index_of_closest + 1], 2);
                            float dist_closest = std::sqrt(diff_xclosest + diff_yclosest);
                            if (dist_curr < dist_closest) {
                                index_of_closest = idx;
                            }
                        }
                        float diff_x = puck_vertices[puck_vertices.size() - 2] - paddle_vec[index_of_closest];
                        float diff_y = puck_vertices[puck_vertices.size() - 1] - paddle_vec[index_of_closest + 1];
                        float mag_of_close_point_and_center = std::sqrt(std::pow(diff_x, 2) + std::pow(diff_y, 2));
                        float leftover_mag = PUCK_RADIUS - mag_of_close_point_and_center;
                        float leftover_x = (diff_x / mag_of_close_point_and_center) * leftover_mag;
                        float leftover_y = (diff_y / mag_of_close_point_and_center) * leftover_mag;

                        for (int idx = 0; idx < puck_vertices.size(); idx += 2) {
                            puck_vertices[idx] += leftover_x;
                            puck_vertices[idx + 1] += leftover_y;
                            puck_vec[idx] = puck_vertices[idx];
                            puck_vec[idx + 1] = puck_vertices[idx + 1];
                        }
                        renderer->update_puck_coords(puck_vec);
                    }
                    renderer->update_paddle_coords(paddle_vec);
                } break;
            }
        }
        if (quit) break;
        renderer->render();
    }
}