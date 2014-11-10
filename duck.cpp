#include "duck.h"
#include <cstdio>
#include <cstdlib>

Duck::Duck(Radian angle, double distance) {
    this->angle = angle;
    this->distance = distance;
    this->duckType = 0;
}
bool Duck::isVisible(Radian playerAngle, Radian fieldOfView) {
    double halfFov = (fieldOfView / 2).toRad();
    double right = playerAngle.toRad() + halfFov;
    double left = right + halfFov;

    return (left <= this->angle.toRad() <= right);
}

double Duck::getDistance() {
    return this->distance;
}

Radian Duck::getAngle() {
    printf("Duck is %f rad\n", this->angle.toRad());
    return this->angle;
}

int Duck::getType() {
    return this->duckType;
}

void Duck::setType(int newType) {
    this->duckType = newType;
}
