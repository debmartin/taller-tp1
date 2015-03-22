/*
 * Coordenada.h
 *
 *  Created on: 21/3/2015
 *      Author: val
 */

#ifndef SRC_MODELO_COORDENADA_H_
#define SRC_MODELO_COORDENADA_H_

class Coordenada{
private:
	int coordenada_x;
	int coordenada_y;

public:
	Coordenada();
	virtual ~Coordenada();
	void setCoordenada(int x, int y);
	int getCoordenadaX();
	int getCoordenadaY();
	void mover_en_X(int delta_x);
	void mover_en_Y(int delta_y);
};

#endif /* SRC_MODELO_COORDENADA_H_ */
