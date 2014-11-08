#ifndef GAME_H
#define GAME_H
#include "SDL2/SDL.h"
class Game {
    SDL_Surface* surface = NULL;
    SDL_Window* window = NULL;
    int width;
    int height;

    void redraw();

    public:
        Game(int, int);
        void run();

};
#endif
