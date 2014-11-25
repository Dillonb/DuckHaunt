#include "duck.h"
Duck::Duck(Radian angle, double distance) {
    this->angle = angle;
    this->distance = distance;
    this->duckType = 0;
}
bool Duck::isVisible(Radian playerAngle, Radian fieldOfView) {
    double player_x = cos(playerAngle.toRad());
    double player_y = sin(playerAngle.toRad());

    double duck_x = cos(this->getAngle().toRad());
    double duck_y = sin(this->getAngle().toRad());

    double dotproduct = (player_x * duck_x) + (player_y * duck_y);

    //printf("Dot product: %f\n", dotproduct);

    return dotproduct > 0;
}

double Duck::getDistance() {
    return this->distance;
}

Radian Duck::getAngle() {
    //printf("Duck is %f rad\n", this->angle.toRad());
    return this->angle;
}

int Duck::getType() {
    return this->duckType;
}

void Duck::setType(int newType) {
    this->duckType = newType;
}
