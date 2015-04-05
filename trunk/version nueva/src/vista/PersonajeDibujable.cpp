/*
 * PersonajeDibujable.cpp
 *
 *  Created on: 25/3/2015
 *      Author: val
 */

#include "PersonajeDibujable.h"


PersonajeDibujable::PersonajeDibujable(Animacion* animIni, Vector2f posicionIni, Vector2f factorEscala, Personaje personajeModelo){
    spritePersonaje = new Sprite(animIni, posicionIni);
    spritePersonaje->escalarConFactor(factorEscala.X(), factorEscala.Y());
    animaciones[animIni->getId()] = animIni;
}

void PersonajeDibujable::setEstado(estado_personaje unEstado){
	this->estado = unEstado;
	seleccionarSprite();
}

void PersonajeDibujable::seleccionarSprite(){

	switch(this->estado){
		case CAMINANDO_DERECHA:
			this->spritePersonaje->cambiarAnimacion(animaciones["zubzero-caminando"]);
			this->spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
			this->spritePersonaje->setTrayectoria(new MRU(spritePersonaje->getPosicion(), Vector2f(180.0f, 0.0f)));
			break;
		case CAMINANDO_IZQUIERDA:
			this->spritePersonaje->cambiarAnimacion(animaciones["zubzero-caminando"]);
			this->spritePersonaje->setSentidoReproduccion(HACIA_ATRAS);
			this->spritePersonaje->setTrayectoria(new MRU(spritePersonaje->getPosicion(), Vector2f(-180.0f, 0.0f)));
			break;
		case EN_ESPERA:
			this->spritePersonaje->cambiarAnimacion(animaciones["zubzero-quieto"]);
			this->spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
			this->spritePersonaje->setTrayectoria(new Reposo(spritePersonaje->getPosicion()));
			break;
		case SALTANDO:
			this->spritePersonaje->cambiarAnimacion(animaciones["zubzero-quieto"]);
			this->spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
			this->spritePersonaje->setTrayectoria(new MRUV(spritePersonaje->getPosicion(), Vector2f(0,-800.0f), Vector2f(0,1600.0f)));
			break;
	}
}

void PersonajeDibujable::setSprite(Sprite* pSprite){
	this->spritePersonaje = pSprite;
}
PersonajeDibujable::~PersonajeDibujable() {
    for (std::map<string, Animacion*>::iterator it = animaciones.begin(); it != animaciones.end(); ++it)
        SDL_DestroyTexture(it->second->getTextura());
}

void PersonajeDibujable::agregarAnimacion(Animacion* nuevaAnimacion){
    animaciones[nuevaAnimacion->getId()] = nuevaAnimacion;
}

void PersonajeDibujable::dibujar(){
	spritePersonaje->dibujar();
}

void PersonajeDibujable::actualizar(){
	spritePersonaje->update();
}

void PersonajeDibujable::actualizarNotificacion(){

	Vector2f posicionEnVentana = this->personaje.obtenerPosicionEnVentana();
	//TODO: Val. Actualizar el sprite con la nueva posicion.
	//Actualizo la posicion del Sprite.
	//this->spritePersonaje->setTrayectoria(new MRU(spritePersonaje->getPosicion(), Vector2f(180.0f, 0.0f)));
}
