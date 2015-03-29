#ifndef SRC_MODELO_VECTOR2F_H_
#define SRC_MODELO_VECTOR2F_H_
#include "Vector2.h"
#include <math.h>

class Vector2f{
private:
	float x;
	float y;

public:
	Vector2f():x(0.0f), y(0.0f) {};
	Vector2f(Vector2 v):x(v.getCoordenadaX()), y(v.getCoordenadaY()) {};
	Vector2f(float xn, float yn): x(xn), y(yn) {};
	virtual ~Vector2f() {};

	float X() { return x; };
	float Y() { return y; };

	Vector2f operator+(const Vector2f& v2) const {
		return Vector2f(x + v2.x, y + v2.y);
	}

	friend Vector2f& operator+=(Vector2f& v1, const Vector2f& v2)	{
		v1.x += v2.x;
		v1.y += v2.y;
		return v1;
	}

	Vector2f operator-(const Vector2f& v2) const {
	return Vector2f(x - v2.x, y - v2.y);
	}

	friend Vector2f& operator-=(Vector2f& v1, const Vector2f& v2) {
		v1.x -= v2.x;
		v1.y -= v2.y;
		return v1;
	}

	Vector2f operator*(float escalar) {
		return Vector2f(x * escalar, y * escalar);
	}

	Vector2f& operator*=(float escalar) {
		x *= escalar;
		y *= escalar;
		return *this;
	}

	operator Vector2() {
		return Vector2(lround(x), lround(y));
	}

};

#endif /* SRC_MODELO_VECTOR2F_H_ */
