/*
 * Vector2.h
 *
 *  Created on: 21/3/2015
 *      Author: val
 */

#ifndef SRC_MODELO_VECTOR2_H_
#define SRC_MODELO_VECTOR2_H_

class Vector2{//TODO: borrar Vector2
private:
	int coordenada_x;
	int coordenada_y;

public:
	Vector2();
	Vector2(int x, int y);
	virtual ~Vector2();
	void setCoordenada(int x, int y);
	int getCoordenadaX();
	int getCoordenadaY();
	void mover_en_X(int delta_x);
	void mover_en_Y(int delta_y);

	Vector2 operator+(const Vector2& v2) const
	{
		return Vector2(coordenada_x + v2.coordenada_x, coordenada_y + v2.coordenada_y);
	}

	friend Vector2& operator+=(Vector2& v1, const Vector2& v2)
	{
		v1.coordenada_x += v2.coordenada_x;
		v1.coordenada_y += v2.coordenada_y;
		return v1;
	}
};

#endif /* SRC_MODELO_VECTOR2_H_ */
