#include "polarcoord.h"


Polarcoord::Polarcoord(Radian theta, double r) {
    this->theta = theta;
    this->r = r;
}
Polarcoord::Polarcoord() {
    this->theta = Radian(0);
    this->r = 0;
}

Polarcoord::Polarcoord(Vector2 position) {
    this->r = sqrt(pow(position.x,2) + pow(position.y,2));
    this->theta = Radian();
    this->theta.radVal = atan2(position.y, position.x);
}

Polarcoord::Polarcoord(const Polarcoord& other) {
    this->theta = other.theta;
    this->r = other.r;
}

Vector2 Polarcoord::toVector2() {
    return Vector2(this->r * cos(this->theta.toRad()), this->r * sin(this->theta.toRad()));
}

Vector2 Polarcoord::toAngleVector2() {
    return Vector2(cos(this->theta.toRad()), sin(this->theta.toRad()));
}
