#ifndef PLAYER_H
#define PLAYER_H

#include "radian.h"
#include "vector2.h"
#include "math.h"
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
        Vector2 getVector();

        int health;
        void loseHealth();
        int getHealth();
};

#endif
