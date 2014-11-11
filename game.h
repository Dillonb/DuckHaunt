#ifndef GAME_H
#define GAME_H
#include <cmath>
#include "SDL2/SDL.h"
#include "SDL2/SDL2_gfxPrimitives.h"
#include "radian.h"
#include "duck.h"
#include "world.h"
#include "opencv2/opencv.hpp"

using namespace cv;

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
    int typeNum;
    int frameCount;
    Mat edges;
    Mat image;
    VideoCapture cap;
    void redraw();

    void drawRadar();

    void drawDucks();

    SDL_Surface* convertToSDLSurface(const Mat&);

    public:
        Game(int, int);
        void run();
};
#endif
