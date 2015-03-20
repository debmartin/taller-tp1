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
using namespace std;

class Personaje {
private:
	float ancho;
	float alto;
	int z_index;
	vector<string> sprites;
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
};

#endif /* SRC_MODELO_PERSONAJE_H_ */
