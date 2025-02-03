#include "Puck.h"
#include "AirHockey.h"

Puck::Puck() {
  vertices = generate_circle_verts(PUCK_RADIUS, 0.0f, 0.0f);
}
