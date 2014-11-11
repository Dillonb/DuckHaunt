#include "duck.h"

Duck::Duck(Radian angle, double distance) {
    this->angle = angle;
    this->distance = distance;
    this->duckType = 0;
}
bool Duck::isVisible(Radian playerAngle, Radian fieldOfView) {
    double pax, pay, dax, day;

    // Player angle vector
    pax = cos(playerAngle.toRad());
    pay = sin(playerAngle.toRad());

    printf("Player angle: (%f, %f)\n", pax, pay);

    // Duck angle vector
    dax = cos(this->angle.toRad());
    day = sin(this->angle.toRad());

    printf("Duck angle: (%f, %f)\n", dax, day);

    // Vector of the left bound
    double lboundx = cos((playerAngle + (fieldOfView / 2)).toRad());
    double lboundy = sin((playerAngle + (fieldOfView / 2)).toRad());

    double bound = pax * lboundx + pay * lboundy;

    printf("BOUND: %f\n", bound);

    double Double = pax * dax + pay * day;

    //double bound = 1 - ((fieldOfView.toRad() / 1) / M_PI);


    //printf("asdf: %f\n", Double);

    //printf("%f\n", ((fieldOfView.toRad() / 2) / M_PI));

    //bool visible = ((fieldOfView.toRad() / 2) / M_PI) > Double;
    bool visible = Double > bound;

    printf("%f > %f\n", Double, bound);

    //printf(visible ? "Visible: True\n" : "Visible: False\n");

    return visible;
}

bool Duck::isVisible(Player p) {
    return isVisible(p.getAngle(), p.getFov());
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
