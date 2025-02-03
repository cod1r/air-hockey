#include "Paddle.h"
#include "AirHockey.h"
#include <fmt/format.h>

Paddle::Paddle() {
  vertices = generate_circle_verts(PADDLE_RADIUS, 0.0f, -0.5f);
}
