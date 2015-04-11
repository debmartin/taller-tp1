/*
 * PersonajeDibujable.cpp
 *
 *  Created on: 25/3/2015
 *      Author: val
 */

#include "PersonajeDibujable.h"


PersonajeDibujable::PersonajeDibujable(Animacion* animIni, Vector2f posicionIni, Vector2f factorEscala, Personaje* personajeModelo) :
    personaje(personajeModelo) {
	spritePersonaje = new Sprite(animIni, posicionIni);
    spritePersonaje->escalarConFactor(factorEscala);
    animaciones[animIni->getId()] = animIni;
}

void PersonajeDibujable::setEstado(estado_personaje unEstado){
	this->estado = unEstado;
	//seleccionarSprite();
}

void PersonajeDibujable::seleccionarSprite(){

	switch(this->estado){
		case CAMINANDO_DERECHA:
			this->spritePersonaje->cambiarAnimacion(animaciones[ID_ZUBZERO_CAMINANDO]);
			this->spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
			break;
		case CAMINANDO_IZQUIERDA:
			this->spritePersonaje->cambiarAnimacion(animaciones[ID_ZUBZERO_CAMINANDO]);
			this->spritePersonaje->setSentidoReproduccion(HACIA_ATRAS);
			break;
		case EN_ESPERA:
			this->spritePersonaje->cambiarAnimacion(animaciones[ID_ZUBZERO_QUIETO]);
			cout<<"Personaje dibujable: Seteo sentido reproduccion"<<endl;
			this->spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
			break;
		case SALTANDO_VERTICAL:
			this->spritePersonaje->cambiarAnimacion(animaciones[ID_ZUBZERO_QUIETO]);
			this->spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
			break;
	}
}

PersonajeDibujable::~PersonajeDibujable() {
    delete spritePersonaje;
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

void PersonajeDibujable::recibirNotificacion(Observable* unObservable){
	cout<<"PersonajeDibujable:Recibio notificacion personaje"<<endl;

	Personaje* unPersonaje = (Personaje*) unObservable;
	Vector2f nueva_posicion = unPersonaje->obtenerPosicionEnVentana();


	//Actualizo la posicion del Sprite.
	this->spritePersonaje->setPosicion(nueva_posicion);

	//Actualizo el estado del personajeDibujable
	setEstado(unPersonaje->getEstado());

	seleccionarSprite();
}
