/*
 * Personaje.h
 *
 *  Created on: 19/3/2015
 *      Author: ariel
 */

#ifndef SRC_MODELO_PERSONAJE_H_
#define SRC_MODELO_PERSONAJE_H_

#include <iostream>
#include <vector>
#include <string.h>
#include "Coordenada.h"
using namespace std;

class Personaje {
private:
	float ancho;
	float alto;
	int z_index;
	vector<string> sprites;
	Coordenada unaCoordenada;

public:
	Personaje();
	virtual ~Personaje();
	float getAlto() const;
	void setAlto(float alto);
	float getAncho() const;
	void setAncho(float ancho);
	vector<string> getSprites() const;
	void setSprites(vector<string> sprites);
	int getIndex() const;
	void setIndex(int index);
	void setPosicion(int posicion_x, int posicion_y);
	Coordenada getPosicion();
	void moverse(int delta_x, int delta_y);
	void saltar();

};

#endif /* SRC_MODELO_PERSONAJE_H_ */
