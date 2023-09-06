#include <iostream>
#include <SDL2/SDL.h>
#include "AirHockey.h"
int main()
{
    AirHockey::AirHockey ah = AirHockey::AirHockey();
    ah.loop();
}