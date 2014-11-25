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

Vector2 Polarcoord::toVector2() {
    return Vector2(this->r * cos(this->theta.toRad()), this->r * sin(this->theta.toRad()));
}
