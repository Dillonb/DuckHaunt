#ifndef DUCK_H
#define DUCK_H

#include <cstdio>
#include <cstdlib>
#include "radian.h"
#include "polarcoord.h"
#include "player.h"
#include "math.h"
#include "SDL2/SDL.h"

class Duck {
	int lastTick;
	int progressDelay;
	int progress;

    public:
        Polarcoord position;
        int frame;
        Duck(Radian, double);
        Duck(Polarcoord);
        bool isVisible(Player);

        int getProgress();
        int getFrame();
        void setFrame(int);
};

#endif
