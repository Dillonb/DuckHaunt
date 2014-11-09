#include "duck.h"

Duck::Duck(Radian angle, double distance) {
    this->angle = angle;
    this->distance = distance;
}
bool Duck::isVisible(Radian playerAngle, Radian fieldOfView) {
    double halfFov = (fieldOfView / 2).toRad();
    double right = playerAngle.toRad() + halfFov;
    double left = right + halfFov;

    return (left <= this->angle.toRad() <= right);
}
