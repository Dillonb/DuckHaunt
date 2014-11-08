#include "radian.h"

Radian::Radian(double val) {
    this->plainNum = val;
    //1 degree is 0.0174532925 radians
    radVal = val * 0.0174532925;
}

void Radian::operator* (double factor) {
    radVal = factor * radVal;
}

double Radian::toRad() {
    return this->radVal;
}
double Radian::toDegrees() {
    plainNum = radVal/0.0174532925;
    return plainNum;
}
