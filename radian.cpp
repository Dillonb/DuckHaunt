#include "radian.h"

Radian::Radian(double val) {
    this->plainNum = val;
    //1 degree is 0.0174532925 radians
    radVal = val * 0.0174532925;
}

void Radian::operator*(double factor) {
    radVal = factor * radVal;
}

void Radian::operator+(double addend) {
    radVal = addend + radVal;
}

void Radian::operator*(Radian factor) {
    radVal = factor.radVal * radVal;
}

void Radian::operator+(Radian addend) {
    radVal = addend.radVal + radVal;
}

double Radian::toRad() {
    return this->radVal;
}
double Radian::toDegrees() {
    plainNum = radVal/0.0174532925;
    return plainNum;
}
