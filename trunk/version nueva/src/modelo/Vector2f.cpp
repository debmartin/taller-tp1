#include "Vector2f.h"

Vector2f Vector2f::operator+(const Vector2f& v2) const {
    return Vector2f(x + v2.x, y + v2.y);
}

Vector2f& Vector2f::operator+=(const Vector2f& v2)	{
    x += v2.x;
    y += v2.y;
    return *this;
}

Vector2f Vector2f::operator-(const Vector2f& v2) const {
    return Vector2f(x - v2.x, y - v2.y);
}

Vector2f& Vector2f::operator-=(const Vector2f& v2) {
    x -= v2.x;
    y -= v2.y;
    return *this;
}

Vector2f Vector2f::operator*(float escalar) {
    return Vector2f(x * escalar, y * escalar);
}

Vector2f& Vector2f::operator*=(float escalar) {
    x *= escalar;
    y *= escalar;
    return *this;
}

//operator Vector2() {
//    return Vector2(lround(x), lround(y));
//}

void Vector2f::setCoordenada(int x, int y) {
    this->x = x;
    this->y = y;
}
