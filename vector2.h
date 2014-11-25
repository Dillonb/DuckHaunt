#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2 {
    public:
        double x;
        double y;

        Vector2(double, double);
        Vector2();
        Vector2& operator=(const Vector2&);
        Vector2 operator*(double);
        Vector2 operator+(Vector2);
        Vector2 operator-(Vector2);
        double dot(Vector2);
        double cross(Vector2);
};


#endif
