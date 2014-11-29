#include "duck.h"
Duck::Duck(Radian angle, double distance) {
    this->position = Polarcoord();

    this->position.theta = angle;
    this->position.r = distance;
    this->frame = 0;
    this->progressDelay = 2000; //2 seconds flat rate atm, in the constructor for different speed ducks l8r
    this->progress = 1; //default 1 but could later set ducks starting at different locations
    this->lastTick = SDL_GetTicks();
}
Duck::Duck(Polarcoord position) {
    this->position = position;
}
bool Duck::isVisible(Player p) {
    // Calculate the cutoff for the dot product of the two vectors used to calculate visibility based on the field of view.
    double cutoff = 1 - (p.getFov().toRad() / M_PI);
    // Calculate the dot product of the duck's position and the player's angle
    double dotproduct = p.getVector().dot(this->position.toAngleVector2());
    // See if the dot product is above the cutoff - if so, the duck is visible.
    return dotproduct > cutoff;
}

int Duck::getFrame() {
    return this->frame;
}

void Duck::setFrame(int newFrame) {
    this->frame = newFrame;
}

int Duck::getProgress() {
    //this is where the delay get checked and the duck is decided to move
    int currentTick = SDL_GetTicks();
    int tickDiff = currentTick - this->lastTick;
    printf("%i\n", tickDiff);
    if (tickDiff > progressDelay)
    {
        printf("prog++");
        this->progress++;
        this->lastTick = currentTick;
    }

    return this->progress;
}
