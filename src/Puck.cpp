#include "Puck.h"
#include <vector>

Puck::Puck()
{
    vec = std::vector<float>(vertices.size());
}

void Puck::update()
{
    for (int i = 0; i < vertices.size(); i += 2) {
        vec[i] = vertices[i];
        vec[i + 1] = vertices[i + 1];
    }
}
