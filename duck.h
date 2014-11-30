#ifndef DUCK_H
#define DUCK_H

#include <cstdio>
#include <cstdlib>
#include "radian.h"
#include "polarcoord.h"
#include "player.h"
#include "math.h"
#include "SDL2/SDL.h"


typedef enum duckStatus_t {
    alive,
    killedByPlayer,
    attackedPlayer,
} duckStatus;

class Duck {
    public:
        Polarcoord position;
        int frame;
        double speed;
        int lastTick;
        int moveCounter;
        int frameCounter;
        Duck(Radian, double);
        Duck(Polarcoord);
        bool isVisible(Player);

        duckStatus status;

        int getFrame();
        void nextFrame();
        void update();
};

#endif
