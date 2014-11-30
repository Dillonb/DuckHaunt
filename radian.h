#ifndef RADIAN_H
#define RADIAN_H
#include "math.h"
#include "vector2.h"
//this class takes a degree value
//it stores the degree and calculate the radian
class Radian {
    public:
        void normalize();
        double radVal;
        Radian(double); // Construct from degrees
        Radian(const Radian&); // Copy constructor
        Radian();
        double toRad();
        double toDegrees();
        Radian operator*(double);
        Radian operator+(double);
        Radian operator-(double);
        Radian operator/(double);
        Radian operator*(Radian);
        Radian operator+(Radian);
        Radian operator-(Radian);
        Radian& operator=(const Radian&);

        void add(Radian amount);
        void subtract(Radian amount);
        void add(double amount);
        void subtract(double amount);

        Vector2 toVector2();

        bool between(Radian, Radian);
};

#endif
