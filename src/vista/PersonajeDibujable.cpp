/*
 * PersonajeDibujable.cpp
 *
 *  Created on: 25/3/2015
 *      Author: val
 */

#include "PersonajeDibujable.h"

PersonajeDibujable::PersonajeDibujable(){
}

void PersonajeDibujable::setEstado(estado_personaje unEstado){
	this->estado = unEstado;
}

void PersonajeDibujable::seleccionarSprite(){
	switch(this->estado){
		case CAMINANDO_DERECHA:
			this->sprites.at(CAMINANDO_DERECHA)->setSentidoReproduccion(HACIA_ADELANTE);
			VentanaGrafica::Instance()->setSprite(this->sprites[CAMINANDO_DERECHA], this->nombre);
			break;
		case CAMINANDO_IZQUIERDA:
			this->sprites[CAMINANDO_IZQUIERDA]->setSentidoReproduccion(HACIA_ATRAS);
			VentanaGrafica::Instance()->setSprite(this->sprites[CAMINANDO_IZQUIERDA], this->nombre);
			break;
		case EN_ESPERA:
			this->sprites[EN_ESPERA]->setSentidoReproduccion(HACIA_ADELANTE);
			VentanaGrafica::Instance()->setSprite(this->sprites[EN_ESPERA], this->nombre);
			break;
		case SALTANDO:
			this->sprites[SALTANDO]->setSentidoReproduccion(HACIA_ADELANTE);
			VentanaGrafica::Instance()->setSprite(this->sprites[SALTANDO], this->nombre);
			break;
	}
}

void PersonajeDibujable::setSprite(Sprite* pSprite){
	//this->sprites.push_back(pSprite);
}
PersonajeDibujable::~PersonajeDibujable() {
	// TODO Auto-generated destructor stub
}
