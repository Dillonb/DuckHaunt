#ifndef DUCK_H
#define DUCK_H

#include <cstdio>
#include <cstdlib>
#include "radian.h"
#include "polarcoord.h"
#include "player.h"
#include "math.h"

class Duck {
    public:
        Polarcoord position;
        int frame;
        Duck(Radian, double);
        Duck(Polarcoord);
        bool isVisible(Player);

        int getFrame();
        void setFrame(int);
};

#endif
