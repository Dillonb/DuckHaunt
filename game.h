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
    SDL_Texture* duckUp = NULL;
    SDL_Texture* duckMid = NULL;
    SDL_Texture* duckDown = NULL;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    int width;
    int height;
    double radarSize;
    World world;

    void redraw();

    void drawRadar();

    void drawDucks();

    public:
        Game(int, int);
        void run();
        void turnLeft(Radian);
        void turnRight(Radian);

};
#endif
