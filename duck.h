#ifndef DUCK_H
#define DUCK_H

#include "radian.h"
#include "polarcoord.h"
#include "player.h"

class Duck {
    public:
        Polarcoord position;
        int duckType;
        Duck(Radian, double);
        Duck(Polarcoord);
        bool isVisible(Player);

        int getType();
        void setType(int);
};

#endif
