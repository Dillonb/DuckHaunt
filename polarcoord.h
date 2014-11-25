#ifndef POLARCOORD_H
#define POLARCOORD_H
#include "radian.h"
#include "vector2.h"
#include "math.h"

class Polarcoord {
    public:
        Radian theta;
        double r;

        Polarcoord(Radian, double);
        Polarcoord(Vector2);
        Polarcoord();
        Polarcoord(const Polarcoord&);

        Vector2 toVector2();
        Vector2 toAngleVector2();
};
#endif
