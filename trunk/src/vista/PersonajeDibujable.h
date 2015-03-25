/*
 * PersonajeDibujable.h
 *
 *  Created on: 25/3/2015
 *      Author: val
 */

#ifndef SRC_VISTA_PERSONAJEDIBUJABLE_H_
#define SRC_VISTA_PERSONAJEDIBUJABLE_H_

#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

enum estado{en_espera, caminando_derecha, caminando_izquierda, saltando};

class PersonajeDibujable{
private:
	vector<string> sprites_caminar;
	vector<string> sprites_saltar;
	vector<string> sprites_en_espera;
	int estado;
	int numero_sprite;
	string sprite_actual;
	void seleccionarSprite();

public:
	PersonajeDibujable();
	virtual ~PersonajeDibujable();
	string obtenerSprite();
	void setEstado(int unEstado);
};

#endif /* SRC_VISTA_PERSONAJEDIBUJABLE_H_ */
