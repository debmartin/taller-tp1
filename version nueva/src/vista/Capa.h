/*
 * Capa.h
 *
 *  Created on: 19/3/2015
 *      Author: ariel
 */

#ifndef SRC_MODELO_CAPA_H_
#define SRC_MODELO_CAPA_H_

#include <iostream>
#include <string.h>
#include "Dibujable.h"
#include "Animacion.h"


using namespace std;

class Capa : public Dibujable{
private:
	Animacion* animacionCapa;
	double ancho;
	Sprite* sprite;
public:
	Capa(Animacion* animCapa, double ancho);
	virtual ~Capa();
	double getAncho() const;
	string getImagenFondo() const;
    void dibujar();
//	friend ostream& operator<<(ostream &o, const Capa &c);
};

#endif /* SRC_MODELO_CAPA_H_ */
