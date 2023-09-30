#include "Puck.h"
#include <climits>
#include <vector>
#include <iostream>

Puck::Puck()
{
    vec = std::vector<float>(vertices.begin(), vertices.end());
    velocity_x = 0.0f;
    velocity_y = 0.0f;
}

void Puck::update()
{
    float add_amt_x = velocity_x;
    float add_amt_y = velocity_y;
    for (int i = 0; i < (int)vertices.size(); i += 2) {
        if (vertices[i] + velocity_x >= 1.0f ||
                vertices[i + 1] + velocity_y >= 1.0f ||
                vertices[i] + velocity_x <= -1.0f ||
                vertices[i + 1] + velocity_y <= -1.0f) {
            if (vertices[i] + velocity_x >= 1.0f) {
                add_amt_x = std::min(add_amt_x, 1.0f - velocity_x);
                velocity_x = -velocity_x;
            } else if (vertices[i] + velocity_x <= -1.0f) {
                add_amt_x = std::min(add_amt_x, -(-1.0f - velocity_x));
                velocity_x = -velocity_x;
            }
            if (vertices[i + 1] + velocity_y >= 1.0f) {
                add_amt_y = std::min(add_amt_y, 1.0f - velocity_y);
                velocity_y = -velocity_y;
            } else if (vertices[i + 1] + velocity_y <= -1.0f) {
                add_amt_y = std::min(add_amt_y, -(-1.0f - velocity_y));
                velocity_y = -velocity_y;
            }
        }
    }
    for (int i = 0; i < (int)vertices.size(); i += 2) {
        vertices[i] += add_amt_x;
        vertices[i + 1] += add_amt_y;
        vec[i] = vertices[i];
        vec[i + 1] = vertices[i + 1];
    }
}
