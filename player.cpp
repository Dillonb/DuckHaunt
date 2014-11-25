#include "player.h"

Player::Player() {
    this->angle = Radian(60);
}

Radian Player::getAngle() {
    return this->angle;
}

Radian Player::getFov() {
    return this->FOV;
}

void Player::turnLeft(Radian amount) {
    this->angle.subtract(amount);
    printf("New angle: %f\n", this->angle.toRad());
}

void Player::turnRight(Radian amount) {
    this->angle.add(amount);
    printf("New angle: %f\n", this->angle.toRad());
}

Vector2 Player::getVector() {
    return Vector2(cos(this->angle.toRad()), sin(this->angle.toRad()));
}
