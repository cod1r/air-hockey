#ifndef _CONSTANTS_H
#define _CONSTANTS_H
namespace CONSTANTS {
static const int NUM_SIDES = 32;
static const int NUM_VERTICES = (NUM_SIDES + 2) * 2;
static const int WINDOW_WIDTH = 606;
static const int WINDOW_HEIGHT = 800;
static const float DECELERATION = 0.9997f;

// some values are from just eyeballing and looking at the values printed for the location
// of my mouse

static const float LEFT_BOUNDARY = -0.96f * WINDOW_WIDTH / WINDOW_HEIGHT;
static const float RIGHT_BOUNDARY = 0.96f * WINDOW_WIDTH / WINDOW_HEIGHT;

static const float TOP_LEFT_BOUNDARY_X = -0.18f * WINDOW_WIDTH / WINDOW_HEIGHT;
static const float TOP_LEFT_BOUNDARY_Y = 0.975f;

static const float TOP_RIGHT_BOUNDARY_X = 0.18f * WINDOW_WIDTH / WINDOW_HEIGHT;
static const float TOP_RIGHT_BOUNDARY_Y = 0.975f;

static const float BOTTOM_LEFT_BOUNDARY_X = -0.18f * WINDOW_WIDTH / WINDOW_HEIGHT;
static const float BOTTOM_LEFT_BOUNDARY_Y = -0.975f;

static const float BOTTOM_RIGHT_BOUNDARY_X = 0.18f * WINDOW_WIDTH / WINDOW_HEIGHT;
static const float BOTTOM_RIGHT_BOUNDARY_Y = -0.975f;
} // namespace CONSTANTS
#endif
