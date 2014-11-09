#ifndef GAME_H
#define GAME_H
#include "SDL2/SDL.h"
#include "radian.h"
#include "duck.h"
#include "world.h"

class Game {
    SDL_Surface* surface = NULL;
    SDL_Window* window = NULL;
    int width;
    int height;
    World world;

    void redraw();

    public:
        Game(int, int);
        void run();

};
#endif
