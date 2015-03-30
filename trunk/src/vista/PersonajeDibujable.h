/*
 * PersonajeDibujable.h
 *
 *  Created on: 25/3/2015
 *      Author: val
 */

#ifndef SRC_VISTA_PERSONAJEDIBUJABLE_H_
#define SRC_VISTA_PERSONAJEDIBUJABLE_H_

#include "VentanaGrafica.h"

#include "Sprite.h"
#include <iostream>
#include <vector>
#include <string.h>
#include "../modelo/Vector2.h"
#include "../modelo/Vector2f.h"
#include "MRU.h"
#include "MRUV.h"

using namespace std;

enum estado_personaje {EN_ESPERA, CAMINANDO_DERECHA, CAMINANDO_IZQUIERDA, SALTANDO};

class PersonajeDibujable{
private:
	Sprite* personaje;
	estado_personaje estado;
	string nombre;

public:
	PersonajeDibujable();
	virtual ~PersonajeDibujable();
	void seleccionarSprite();
	void setEstado(estado_personaje unEstado);
	void setSprite(Sprite* pSprite);
};

#endif /* SRC_VISTA_PERSONAJEDIBUJABLE_H_ */
