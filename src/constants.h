#ifndef _CONSTANTS_H
#define _CONSTANTS_H
#include <array>
#include <cmath>
#include <numbers>
namespace CONSTANTS {
static const int NUM_SIDES = 32;
static const int NUM_VERTICES = (NUM_SIDES + 2) * 2;
static const float COEFFICIENT_OF_FRICTION_STATIC = 0.03f;
static const float COEFFICIENT_OF_FRICTION_DYNAMIC = 0.02f;
static const int WINDOW_WIDTH = 800;
static const int WINDOW_HEIGHT = 800;
} // namespace CONSTANTS
#endif
