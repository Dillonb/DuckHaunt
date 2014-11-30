#include "vector2.h"

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

double Vector2::magnitude() {
    return sqrt(pow(this->x,2) + pow(this->y,2));
}

int Vector2::rightOf(Vector2 other) {
    Vector2 temp(-1 * this->y, this->x); // Rotate this vector 90 degrees counter clockwise
    double result = other.dot(temp);
    return (result > 0) ? 1 : ((result < 0) ? -1 : 0);

}
