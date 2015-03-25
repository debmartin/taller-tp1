/*
 * PersonajeDibujable.cpp
 *
 *  Created on: 25/3/2015
 *      Author: val
 */

#include "PersonajeDibujable.h"

PersonajeDibujable::PersonajeDibujable(){
}

void PersonajeDibujable::setEstado(int unEstado){
	this->estado = unEstado;
}

void PersonajeDibujable::seleccionarSprite(){
	switch(this->estado){
		case caminando_derecha:
			this->sprite_actual = this->sprites_caminar[this->numero_sprite];
			break;
		case caminando_izquierda:
			this->sprite_actual = this->sprites_caminar[this->numero_sprite];
			break;
		case en_espera:
			this->sprite_actual = this->sprites_en_espera[this->numero_sprite];
			break;
		case saltando:
			this->sprite_actual = this->sprites_saltar[this->numero_sprite];
			break;
	}
}

string PersonajeDibujable::obtenerSprite(){
	seleccionarSprite();
	return this->sprite_actual;
}
PersonajeDibujable::~PersonajeDibujable() {
	// TODO Auto-generated destructor stub
}
