#ifndef _AIR_HOCKEY_H
#define _AIR_HOCKEY_H
#include "constants.h"
#include <SDL2/SDL.h>
#include <array>
class Puck;
class Paddle;
class Renderer;
class AirHockey {
public:
  Puck *puck_inter;
  Puck *puck;
  Paddle *paddle;
  Renderer *renderer = nullptr;
  void determine_puck_velocity_when_collided(Puck* puck, const Paddle* paddle);
  void update_puck();
  void update_paddle();
  AirHockey();
  ~AirHockey();
  void loop();
};
std::array<float, CONSTANTS::NUM_VERTICES>
generate_circle_verts(float radius, float offsetx, float offsety);
#endif
