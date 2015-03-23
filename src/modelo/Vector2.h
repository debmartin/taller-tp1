/*
 * Vector2.h
 *
 *  Created on: 21/3/2015
 *      Author: val
 */

#ifndef SRC_MODELO_VECTOR2_H_
#define SRC_MODELO_VECTOR2_H_

class Vector2{
private:
	int coordenada_x;
	int coordenada_y;

public:
	Vector2();
	virtual ~Vector2();
	void setCoordenada(int x, int y);
	int getCoordenadaX();
	int getCoordenadaY();
	void mover_en_X(int delta_x);
	void mover_en_Y(int delta_y);
};

#endif /* SRC_MODELO_VECTOR2_H_ */
