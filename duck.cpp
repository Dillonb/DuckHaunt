#include "duck.h"
#include <cstdio>
#include <cstdlib>

Duck::Duck(Radian angle, double distance) {
    this->position = Polarcoord();

    this->position.theta = angle;
    this->position.r = distance;
    this->duckType = 0;
}
Duck::Duck(Polarcoord position) {
    this->position = position;
}
bool Duck::isVisible(Player p) {
    double dotproduct = p.getVector().dot(this->position.toVector2());
    printf("Dot product: %f\n", dotproduct);
    return dotproduct > 0;

}

int Duck::getType() {
    return this->duckType;
}

void Duck::setType(int newType) {
    this->duckType = newType;
}
