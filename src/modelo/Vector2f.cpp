#include "Vector2f.h"

#include <sstream>

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

void Vector2f::setCoordenada(int x, int y) {
    this->x = x;
    this->y = y;
}

ostream& operator <<(ostream &o, const Vector2f &v) {
        o<<"["<< v.x <<", "<< v.y <<"]";
        return o;
}

string Vector2f::toString() {
    ostringstream stream;
    stream <<*this;
	return stream.str();
}
