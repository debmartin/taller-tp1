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
	seleccionarSprite();
}

void PersonajeDibujable::seleccionarSprite(){

	switch(this->estado){
		case CAMINANDO_DERECHA:
			this->personaje->cambiarAnimacion("zubzero-caminando");
			this->personaje->setSentidoReproduccion(HACIA_ADELANTE);
			this->personaje->setTrayectoria(new MRU(personaje->getPosicion(), Vector2f(180.0f, 0.0f)));
			break;
		case CAMINANDO_IZQUIERDA:
			this->personaje->cambiarAnimacion("zubzero-caminando");
			this->personaje->setSentidoReproduccion(HACIA_ATRAS);
			this->personaje->setTrayectoria(new MRU(personaje->getPosicion(), Vector2f(-180.0f, 0.0f)));
			break;
		case EN_ESPERA:
			this->personaje->cambiarAnimacion("zubzero-quieto");
			this->personaje->setSentidoReproduccion(HACIA_ADELANTE);
			this->personaje->setTrayectoria(new Reposo(personaje->getPosicion()));
			break;
		case SALTANDO:
			this->personaje->cambiarAnimacion("zubzero-quieto");
			this->personaje->setSentidoReproduccion(HACIA_ADELANTE);
			this->personaje->setTrayectoria(new MRUV(personaje->getPosicion(), Vector2f(0,-800.0f), Vector2f(0,1600.0f)));
			break;
	}
}

void PersonajeDibujable::setSprite(Sprite* pSprite){
	this->personaje = pSprite;
}
PersonajeDibujable::~PersonajeDibujable() {
	// TODO Auto-generated destructor stub
}