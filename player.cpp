#include "player.h"

Player::Player() {
    this->angle = Radian(0);
    this->FOV = Radian(60);
    this->health = 5;
}

Radian Player::getAngle() {
    return this->angle;
}

Radian Player::getFov() {
    return this->FOV;
}

void Player::turnLeft(Radian amount) {
    this->angle.add(amount);
    printf("New angle: %f\n", this->angle.toRad());
}

void Player::turnRight(Radian amount) {
    this->angle.subtract(amount);
    printf("New angle: %f\n", this->angle.toRad());
}

Vector2 Player::getVector() {
    Vector2 pvector(cos(this->angle.toRad()), sin(this->angle.toRad()));
    return pvector;
}

void Player::loseHealth() {
    health--;
}

int Player::getHealth() {
    return health;
}

int Player::getScore() {
    return this->score;
}
void Player::setScore(int newScore) {
    this->score = newScore;
}
void Player::addScore(int addend) {
    this->score += addend;
}
