#ifndef RADIAN_H
#define RADIAN_H
//this class takes a degree value
//it stores the degree and calculate the radian
class Radian {
    double plainNum;
    double radVal;


    public:
        Radian(double);
        double toRad();
        double toDegrees();
        void operator*(double);
};

#endif
