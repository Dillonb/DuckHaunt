#ifndef DUCK_H
#define DUCK_H

#include "radian.h"

class Duck {
    Radian angle;
    double distance;

    public:
        Duck(Radian, double);
        bool isVisible(Radian, Radian);
};

#endif
