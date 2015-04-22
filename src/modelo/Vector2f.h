#ifndef SRC_MODELO_VECTOR2F_H_
#define SRC_MODELO_VECTOR2F_H_
#include <math.h>

#include <iostream>
#include <string>
using namespace std;

class Vector2f{
private:
	float x;
	float y;

public:
	Vector2f(float xn = 0.0f, float yn = 0.0f): x(xn), y(yn) {};
	virtual ~Vector2f() {};

	float X() const { return x; };
	float Y() const { return y; };

	Vector2f operator+(const Vector2f& v2) const;
	Vector2f& operator+=(const Vector2f& v2);
	Vector2f operator-(const Vector2f& v2) const;
	Vector2f& operator-=(const Vector2f& v2);
	Vector2f operator*(float escalar);
	Vector2f& operator*=(float escalar);
    void setCoordenada(int x, int y);

    friend ostream& operator<<(ostream &o, const Vector2f &c);
    string toString();
};

#endif /* SRC_MODELO_VECTOR2F_H_ */
