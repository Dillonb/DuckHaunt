#ifndef DUCK_H
#define DUCK_H

#include <cstdio>
#include <cstdlib>
#include "radian.h"

class Duck {
    Radian angle;
    double distance;
    int duckType;

    public:
        Duck(Radian, double);
        bool isVisible(Radian, Radian);

        double getDistance();
        Radian getAngle();
        int getType();
        void setType(int);
};

#endif
