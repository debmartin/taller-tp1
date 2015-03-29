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

	Vector2 posActual;
	Vector2 velActual;
	switch(this->estado){
		case CAMINANDO_DERECHA:
			/*
			this->sprites[CAMINANDO_DERECHA]->setSentidoReproduccion(HACIA_ADELANTE);
			this->sprites[CAMINANDO_DERECHA]->desplazar(Vector2(5,0));
			++++
			this->sprites[EN_ESPERA]->desplazar(Vector2(5,0));
			VentanaGrafica::Instance()->setSprite(this->sprites[CAMINANDO_DERECHA], this->nombre);
			*/
			posActual = sprites[CAMINANDO_DERECHA]->getPosicion();
			velActual = Vector2f(100.0f, 0.0f);
			this->sprites[CAMINANDO_DERECHA]->setSentidoReproduccion(HACIA_ADELANTE);
			this->sprites[CAMINANDO_DERECHA]->setTrayectoria(new MRU(posActual, velActual));
			this->sprites[EN_ESPERA]->setTrayectoria(new MRU(posActual, velActual));
			VentanaGrafica::Instance()->setSprite(this->sprites[CAMINANDO_DERECHA], this->nombre);
			cout << "UN PASO DERECHA" << endl;
			break;
		case CAMINANDO_IZQUIERDA:
			this->sprites[CAMINANDO_IZQUIERDA]->setSentidoReproduccion(HACIA_ATRAS);
			this->sprites.at(CAMINANDO_DERECHA)->desplazar(Vector2(-5,0));
			this->sprites.at(EN_ESPERA)->desplazar(Vector2(-5,0));
			VentanaGrafica::Instance()->setSprite(this->sprites[CAMINANDO_IZQUIERDA], this->nombre);
			break;
		case EN_ESPERA:
			/*
			this->sprites[EN_ESPERA]->setSentidoReproduccion(HACIA_ADELANTE);
			VentanaGrafica::Instance()->setSprite(this->sprites[EN_ESPERA], this->nombre);
			*/
			this->sprites[EN_ESPERA]->setSentidoReproduccion(HACIA_ADELANTE);
			this->sprites[EN_ESPERA]->setTrayectoria(new Reposo(posActual));
			VentanaGrafica::Instance()->setSprite(this->sprites[EN_ESPERA], this->nombre);
			break;
		case SALTANDO:
			this->sprites[SALTANDO]->setSentidoReproduccion(HACIA_ADELANTE);
			VentanaGrafica::Instance()->setSprite(this->sprites[SALTANDO], this->nombre);
			break;
	}
}

void PersonajeDibujable::setSprite(Sprite* pSprite){
	this->sprites.push_back(pSprite);
}
PersonajeDibujable::~PersonajeDibujable() {
	// TODO Auto-generated destructor stub
}
