/*
 * PersonajeDibujable.h
 *
 *  Created on: 25/3/2015
 *      Author: val
 */

#ifndef SRC_VISTA_PERSONAJEDIBUJABLE_H_
#define SRC_VISTA_PERSONAJEDIBUJABLE_H_

#include "Sprite.h"
#include "VentanaGrafica.h"
#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

enum estado{en_espera, caminando_derecha, caminando_izquierda, saltando};
enum SentidoReproduccion{derecha, izquierda};

class PersonajeDibujable{
private:
	vector<Sprite> sprites;
	int estado;

public:
	PersonajeDibujable();
	virtual ~PersonajeDibujable();
	void seleccionarSprite();
	void setEstado(int unEstado);
	void setSprite(Sprite unSprite);
};

#endif /* SRC_VISTA_PERSONAJEDIBUJABLE_H_ */
