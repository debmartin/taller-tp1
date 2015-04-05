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
#include "Sprite.h"
#include "../modelo/Vector2f.h"

using namespace std;

class Capa : public Dibujable{
private:
	Animacion* animacionCapa;
	Vector2f tamanio;
	Sprite* sprite;
public:
	Capa(Animacion* animCapa, Vector2f& tamInicial, Vector2f& posInicial);
	virtual ~Capa();
	double getAncho();
//	string getImagenFondo() const;
    void dibujar();
    void actualizar();
//	friend ostream& operator<<(ostream &o, const Capa &c);
};

#endif /* SRC_MODELO_CAPA_H_ */
