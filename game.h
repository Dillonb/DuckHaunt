#ifndef GAME_H
#define GAME_H
#include <math.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL2_gfxPrimitives.h"
#include "radian.h"
#include "duck.h"
#include "world.h"

class Game {
    SDL_Surface* surface = NULL;
    SDL_Texture* texture = NULL;
    SDL_Texture* radarTexture = NULL;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    int width;
    int height;
    int radarSize;
    World world;

    void redraw();

    void drawRadar();

    public:
        Game(int, int);
        void run();

};
#endif
