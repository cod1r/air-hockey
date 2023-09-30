#include "AirHockey.h"
#include "Renderer.h"
#include "Paddle.h"
#include "Puck.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <format>
#include <filesystem>
#include <cassert>
AirHockey::AirHockey()
{
    puck_inter = new Puck();
    puck = new Puck();
    paddle = new Paddle();
    renderer = new Renderer();
    std::vector<float> puck_coords(puck->vertices.begin(), puck->vertices.end());
    renderer->init_puck(puck_coords);
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
        bool mouse_ev = false;
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
                    paddle->update((e.motion.x - 500.0f) / 500.0f, -(e.motion.y - 500.0f) / 500.0f);
                    mouse_ev = true;
                } break;
            }
        }
        if (quit) break;
        bool collided = false;
        float prev_y_paddle = paddle->vec[paddle->vec.size() - 1] - paddle->velocity_y;
        float prev_x_paddle = paddle->vec[paddle->vec.size() - 2] - paddle->velocity_x;
        float distance_between_two_centers = std::sqrt(std::pow(puck->vertices[puck->vertices.size() - 2] - paddle->vec[paddle->vec.size() - 2], 2.0f) + std::pow(puck->vertices[puck->vertices.size() - 1] - paddle->vec[paddle->vec.size() - 1], 2.0f));
        float distance_between_old_paddle_and_puck = std::sqrt(std::pow(prev_x_paddle - puck->vertices[puck->vertices.size() - 2], 2.0f) + std::pow(prev_y_paddle - puck->vertices[puck->vertices.size() - 1], 2.0f));
        if (((
        (prev_x_paddle - PADDLE_RADIUS <= puck->vertices[puck->vertices.size() - 2] - PUCK_RADIUS && puck->vertices[puck->vertices.size() - 2] + PUCK_RADIUS <= paddle->vec[paddle->vec.size() - 2] + PADDLE_RADIUS)
        || (prev_x_paddle - PADDLE_RADIUS >= puck->vertices[puck->vertices.size() - 2] - PUCK_RADIUS && puck->vertices[puck->vertices.size() - 2] + PUCK_RADIUS >= paddle->vec[paddle->vec.size() - 2] + PADDLE_RADIUS))
        && ((prev_y_paddle - PADDLE_RADIUS <= puck->vertices[puck->vertices.size() - 1] - PUCK_RADIUS && puck->vertices[puck->vertices.size() - 1] + PUCK_RADIUS <= paddle->vec[paddle->vec.size() - 1] + PADDLE_RADIUS)
        || (prev_y_paddle - PADDLE_RADIUS >= puck->vertices[puck->vertices.size() - 1] - PUCK_RADIUS && puck->vertices[puck->vertices.size() - 1] + PUCK_RADIUS >= paddle->vec[paddle->vec.size() - 1] + PADDLE_RADIUS)))
        || (distance_between_two_centers <= PUCK_RADIUS + PADDLE_RADIUS)) {
            if (puck->velocity_y > 0 && puck->velocity_x > 0 && paddle->velocity_y > 0 && paddle->velocity_x > 0) {
            } else if (paddle->velocity_x > 0 || paddle->velocity_y > 0) {
                if (paddle->velocity_x == 0) {
                } else if (paddle->velocity_y == 0) {
                } else {
                    float slope_paddle = paddle->velocity_y / paddle->velocity_x;
                    float y_offset_paddle = prev_y_paddle - slope_paddle * prev_x_paddle;
                    float perpendicular_slope = -paddle->velocity_x / paddle->velocity_y;
                    float y_offset_puck = puck->vertices[puck->vertices.size() - 1] - perpendicular_slope * puck->vertices[puck->vertices.size() - 2];
                    float x_intersection = (y_offset_puck - y_offset_paddle) / (slope_paddle - perpendicular_slope);
                    float y_intersection = slope_paddle * x_intersection + y_offset_paddle;
                    float length_1 = std::sqrt(std::pow(puck->vertices[puck->vertices.size() - 2] - x_intersection, 2.0f) + std::pow(puck->vertices[puck->vertices.size() - 1] - y_intersection, 2.0f));
                    if (std::sqrt(std::pow(x_intersection - puck->vertices[puck->vertices.size() - 2], 2.0f) + std::pow(y_intersection - puck->vertices[puck->vertices.size() - 1], 2.0f)) <= PUCK_RADIUS + PADDLE_RADIUS) {
                        float collision_paddle_y;
                        float collision_paddle_x;
                        if (length_1 > 0.0f) {
                            float length_3 = std::sqrt(std::pow(PUCK_RADIUS + PADDLE_RADIUS, 2.0f) - std::pow(length_1, 2.0f));
                            float length_x = std::cos(std::atan(slope_paddle)) * length_3;
                            if (prev_x_paddle < puck->vertices[puck->vertices.size() - 2]) {
                                length_x = -length_x;
                            }
                            collision_paddle_x = x_intersection + length_x;
                            collision_paddle_y = slope_paddle * collision_paddle_x + y_offset_paddle;

                            puck_inter->vec = std::vector<float>(puck_inter->vertices.begin(), puck_inter->vertices.end());
                        } else {
                            float x_offset = std::cos(std::atan(slope_paddle)) * (PUCK_RADIUS + PADDLE_RADIUS);
                            if (prev_x_paddle < puck->vertices[puck->vertices.size() - 2]) {
                                x_offset = -x_offset;
                            }
                            collision_paddle_x = puck->vertices[puck->vertices.size() - 2] + x_offset;
                            collision_paddle_y = slope_paddle * collision_paddle_x + y_offset_paddle;
                        }
                        float collide_slope = (collision_paddle_y - puck->vertices[puck->vertices.size() - 1]) / (collision_paddle_x - puck->vertices[puck->vertices.size() - 2]);
                        float x_puck_collide_offset = std::cos(std::atan(collide_slope)) * PUCK_RADIUS;
                        if (prev_x_paddle < puck->vertices[puck->vertices.size() - 2]) {
                            x_puck_collide_offset = -x_puck_collide_offset;
                        }
                        float x_puck_collision = puck->vertices[puck->vertices.size() - 2] + x_puck_collide_offset;
                        float y_puck_collide_offset = puck->vertices[puck->vertices.size() - 1] - collide_slope * puck->vertices[puck->vertices.size() - 2];
                        float y_puck_collision = collide_slope * x_puck_collision + y_puck_collide_offset;

                        float diff_x = puck->vertices[puck->vertices.size() - 2] - x_puck_collision;
                        float diff_y = puck->vertices[puck->vertices.size() - 1] - y_puck_collision;
                        float mag_of_close_point_and_center = std::sqrt(std::pow(diff_x, 2) + std::pow(diff_y, 2));
                        float magnitude = std::sqrt(std::pow(paddle->velocity_x, 2.0f) + std::pow(paddle->velocity_y, 2.0f));
                        if (mag_of_close_point_and_center > 0) {
                            puck->velocity_x = (diff_x / mag_of_close_point_and_center) * magnitude ;
                            puck->velocity_y = (diff_y / mag_of_close_point_and_center) * magnitude ;
                        }
                    }
                }
            } else if (puck->velocity_x > 0 || puck->velocity_y > 0) {
            }
        }
        if (!mouse_ev) {
            paddle->velocity_x = 0;
            paddle->velocity_y = 0;
        }
        puck->update();
        renderer->update_puck_coords(puck->vec);
        renderer->update_puck_inter_coords(puck_inter->vec);
        renderer->update_paddle_coords(paddle->vec);
        renderer->render();
    }
}
