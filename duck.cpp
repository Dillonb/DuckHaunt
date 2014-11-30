#include "duck.h"
Duck::Duck(Radian angle, double distance) {
    this->position = Polarcoord();

    this->position.theta = angle;
    this->position.r = distance;
    this->frame = 0;
}
Duck::Duck(Polarcoord position) {
    this->position = position;
}
bool Duck::isVisible(Player p) {
    // Calculate the cutoff for the dot product of the two vectors used to calculate visibility based on the field of view.
    double cutoff = 1 - (p.getFov().radVal / (2 * M_PI));
    printf("CUTOFF: %f\n", cutoff);
    // Calculate the dot product of the duck's position and the player's angle
    double dotproduct = p.getVector().dot(this->position.toAngleVector2());
    // See if the dot product is above the cutoff - if so, the duck is visible.
    printf("DOTPRODUCT: %f\n", dotproduct);
    return dotproduct > cutoff;
}

int Duck::getFrame() {
    return this->frame;
}

void Duck::setFrame(int newFrame) {
    this->frame = newFrame;
}
