#ifndef PLAYER_H
#define PLAYER_H

#include "radian.h"
#include <cstdlib>
#include <cstdio>

class Player {

    public:
        Player();
        Radian angle;
        Radian FOV;
        void turnRight(Radian);
        void turnLeft(Radian);
        Radian getAngle();
        Radian getFov();
};

#endif
