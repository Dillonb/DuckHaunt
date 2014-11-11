#ifndef DUCK_H
#define DUCK_H

#include "radian.h"
#include "player.h"
#include <cstdio>
#include <cstdlib>
#include <cmath>

class Duck {
    Radian angle;
    double distance;
    int duckType;

    public:
        Duck(Radian, double);
        bool isVisible(Radian, Radian);
        bool isVisible(Player);

        double getDistance();
        Radian getAngle();
        int getType();
        void setType(int);
};

#endif
