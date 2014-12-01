#ifndef GAME_H
#define GAME_H
#include <math.h>
#include <cstdio>
#include <cstdlib>
#include <zlib.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL2_gfxPrimitives.h"
#include "SDL2/SDL_mixer.h"
#include "radian.h"
#include "duck.h"
#include "world.h"
#include "polarcoord.h"
//#include "opencv2/opencv.hpp"

#define EXIT_RESTART 1
#define EXIT_QUIT 2

#define TRIGGER_PIN 8
#define RIGHT_PIN 9
#define LEFT_PIN 7

//using namespace cv;

typedef enum gameState_t {
    titleScreen,
    game,
    gameOver,
} gameState;

class Game {
    SDL_Surface* surface = NULL;
    SDL_Texture* texture = NULL;
    SDL_Texture* radarTexture = NULL;
    SDL_Texture* titleScreenTexture = NULL;
    SDL_Texture* spriteTexture;
    SDL_Texture* backgroundTexture = NULL;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* crosshairTexture;
    TTF_Font* eightbitwonder = NULL;
    Uint32 lastTicks;
    Uint32 gameStartTicks;
    int width;
    int height;
    double radarSize;
    World world;
    int typeNum;
    int frameCount;
    int duckCounter;
    //Mat edges;
    //Mat image;
    //VideoCapture cap;
    Mix_Chunk *Laser;
    Mix_Chunk *GameOver;
    Mix_Chunk *DeadDuck;
    Mix_Chunk *bg;

    gameState state;

    void redraw();

    void drawRadar();

    void drawHealth();

    void drawDucks();

    void drawScore();

    //SDL_Surface* convertToSDLSurface(const Mat&);

    public:
        Game(int, int);
        ~Game();
        int run();
};
#endif
