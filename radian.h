#ifndef RADIAN_H
#define RADIAN_H
//this class takes a degree value
//it stores the degree and calculate the radian
class Radian {
    double radVal;


    void normalize();

    public:
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

        bool between(Radian, Radian);
};

#endif
