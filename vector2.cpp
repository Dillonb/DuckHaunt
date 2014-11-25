#include "vector2.h"
#include <cstdlib>
#include <cstdio>

Vector2::Vector2(double x, double y) {
    this->x = x;
    this->y = y;
}
Vector2::Vector2() {
    this->x = 0;
    this->y = 0;
}

Vector2& Vector2::operator=(const Vector2& other) {
    this->x = other.x;
    this->y = other.y;
}
Vector2 Vector2::operator+(Vector2 other) {
    Vector2 temp;
    temp.x = this->x + other.x;
    temp.y = this->y + other.y;
    return temp;
}
Vector2 Vector2::operator-(Vector2 other) {
    Vector2 temp;
    temp.x = this->x - other.x;
    temp.y = this->y - other.y;
    return temp;
}
Vector2 Vector2::operator*(double multiplicand) {
    Vector2 temp;
    temp.x = this->x * multiplicand;
    temp.y = this->y * multiplicand;
    return temp;
}
double Vector2::dot(Vector2 other) {
    return (this->x * other.x) + (this->y * other.y);
}
