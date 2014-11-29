#ifndef POINT_H
#define POINT_H
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include "radian.h"
#include "cartesian.h"
//this class takes a degree value
//it stores the degree and calculate the radian
class Point {
    Radian theta;
    int radius;

    void normalize();

    public:
        Point(int, double); // Construct from degrees
        Point(int, Radian);	// predefined radians
        Point(const Point&); // Copy constructor
        Point();			// blank constructor
        struct cartesian toXY();
        bool between(Radian, Radian); // should be passed two Radian values for players L.FOV and R.FOV
};

#endif
