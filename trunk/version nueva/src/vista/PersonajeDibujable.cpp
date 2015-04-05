/*
 * PersonajeDibujable.cpp
 *
 *  Created on: 25/3/2015
 *      Author: val
 */

#include "PersonajeDibujable.h"


PersonajeDibujable::PersonajeDibujable(Animacion* animIni, Vector2f posicionIni, Vector2f factorEscala){
    personaje = new Sprite(animIni, posicionIni);
    personaje->escalarConFactor(factorEscala.X(), factorEscala.Y());
    animaciones[animIni->getId()] = animIni;
}

void PersonajeDibujable::setEstado(estado_personaje unEstado){
	this->estado = unEstado;
	seleccionarSprite();
}

void PersonajeDibujable::seleccionarSprite(){

	switch(this->estado){
		case CAMINANDO_DERECHA:
			this->personaje->cambiarAnimacion(animaciones["zubzero-caminando"]);
			this->personaje->setSentidoReproduccion(HACIA_ADELANTE);
			this->personaje->setTrayectoria(new MRU(personaje->getPosicion(), Vector2f(180.0f, 0.0f)));
			break;
		case CAMINANDO_IZQUIERDA:
			this->personaje->cambiarAnimacion(animaciones["zubzero-caminando"]);
			this->personaje->setSentidoReproduccion(HACIA_ATRAS);
			this->personaje->setTrayectoria(new MRU(personaje->getPosicion(), Vector2f(-180.0f, 0.0f)));
			break;
		case EN_ESPERA:
			this->personaje->cambiarAnimacion(animaciones["zubzero-quieto"]);
			this->personaje->setSentidoReproduccion(HACIA_ADELANTE);
			this->personaje->setTrayectoria(new Reposo(personaje->getPosicion()));
			break;
		case SALTANDO:
			this->personaje->cambiarAnimacion(animaciones["zubzero-quieto"]);
			this->personaje->setSentidoReproduccion(HACIA_ADELANTE);
			this->personaje->setTrayectoria(new MRUV(personaje->getPosicion(), Vector2f(0,-800.0f), Vector2f(0,1600.0f)));
			break;
	}
}

void PersonajeDibujable::setSprite(Sprite* pSprite){
	this->personaje = pSprite;
}
PersonajeDibujable::~PersonajeDibujable() {
    for (std::map<string, Animacion*>::iterator it = animaciones.begin(); it != animaciones.end(); ++it)
        SDL_DestroyTexture(it->second->getTextura());
}

void PersonajeDibujable::agregarAnimacion(Animacion* nuevaAnimacion){
    animaciones[nuevaAnimacion->getId()] = nuevaAnimacion;
}

void PersonajeDibujable::dibujar(){
    personaje->dibujar();
}

void PersonajeDibujable::actualizar(){
    personaje->update();
}