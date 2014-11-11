#include "radian.h"

Radian::Radian(double val) {
    //1 degree is 0.0174532925 radians
    radVal = val * 0.0174532925;
    normalize();
}

Radian::Radian() {
    this->radVal = 0;
}

Radian::Radian(const Radian& other) {
    this->radVal = other.radVal;
}

Radian Radian::operator*(double factor) {
    Radian temp;
    temp.radVal = radVal * factor;
    temp.normalize();
    return temp;
}

Radian Radian::operator+(double addend) {
    Radian temp;
    temp.radVal = radVal + addend;
    temp.normalize();
    return temp;
}

Radian Radian::operator-(double subtrahend) {
    Radian temp;
    temp.radVal = radVal - subtrahend;
    temp.normalize();
    return temp;
}

Radian Radian::operator-(Radian subtrahend) {
    Radian temp;
    temp.radVal = radVal - subtrahend.radVal;
    temp.normalize();
    return temp;
}

Radian Radian::operator*(Radian factor) {
    Radian temp;
    temp.radVal = radVal * factor.radVal;
    temp.normalize();
    return temp;
}

Radian Radian::operator+(Radian addend) {
    Radian temp;
    temp.radVal = radVal + addend.radVal;
    temp.normalize();
    return temp;
}

void Radian::add(double amount) {
    this->radVal += amount;
    normalize();
}

void Radian::add(Radian amount) {
    this->radVal += amount.radVal;
    normalize();
}

void Radian::subtract(double amount) {
    this->radVal -= amount;
    normalize();
}

void Radian::subtract(Radian amount) {
    this->radVal -= amount.radVal;
    normalize();
}

Radian Radian::operator/(double divisor) {
    Radian temp;
    temp.radVal = radVal / divisor;
    temp.normalize();
    return temp;
}

Radian Radian::operator=(Radian other) {
    this->radVal = other.radVal;
}

double Radian::toRad() {
    return this->radVal;
}

double Radian::toDegrees() {
    return radVal/0.0174532925;
}

// Normalizes a radian value - if it's more than 2PI, keep subtracting 2PI until it's not
// If it's less than 0, keep addding 2PI until it's not
void Radian::normalize() {
    while (this->radVal >= 2 * M_PI) {
        this->radVal -= 2 * M_PI;
    }
    while (this->radVal < 0) {
        this->radVal += 2 * M_PI;
    }
}
