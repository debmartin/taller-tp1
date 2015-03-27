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

using namespace std;

enum estado{en_espera, caminando_derecha, caminando_izquierda, saltando};

class PersonajeDibujable{
private:
	vector<Sprite*> sprites;
	int estado;
	string nombre;

public:
	PersonajeDibujable();
	virtual ~PersonajeDibujable();
	void seleccionarSprite();
	void setEstado(int unEstado);
	void setSprite(Sprite* pSprite);
};

#endif /* SRC_VISTA_PERSONAJEDIBUJABLE_H_ */
