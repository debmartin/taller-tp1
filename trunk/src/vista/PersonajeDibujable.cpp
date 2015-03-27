/*
 * PersonajeDibujable.cpp
 *
 *  Created on: 25/3/2015
 *      Author: val
 */

#include "PersonajeDibujable.h"

PersonajeDibujable::PersonajeDibujable(){
	estado = en_espera;
}

void PersonajeDibujable::setEstado(int unEstado){
	this->estado = unEstado;
}

void PersonajeDibujable::seleccionarSprite(){
	switch(this->estado){
		case caminando_derecha:
			this->sprites.at(caminando_derecha)->setSentidoReproduccion(HACIA_ADELANTE);
			VentanaGrafica::Instance()->setSprite(this->sprites[caminando_derecha], this->nombre);
			break;
		case caminando_izquierda:
			this->sprites[caminando_izquierda]->setSentidoReproduccion(HACIA_ATRAS);
			VentanaGrafica::Instance()->setSprite(this->sprites[caminando_izquierda], this->nombre);
			break;
		case en_espera:
			this->sprites[en_espera]->setSentidoReproduccion(HACIA_ADELANTE);
			VentanaGrafica::Instance()->setSprite(this->sprites[en_espera], this->nombre);
			break;
		case saltando:
			this->sprites[saltando]->setSentidoReproduccion(HACIA_ADELANTE);
			VentanaGrafica::Instance()->setSprite(this->sprites[saltando], this->nombre);
			break;
	}
}

void PersonajeDibujable::setSprite(Sprite* pSprite){
	//this->sprites.push_back(pSprite);
}
PersonajeDibujable::~PersonajeDibujable() {
	// TODO Auto-generated destructor stub
}
