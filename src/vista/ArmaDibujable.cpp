/*
 * ArmaDibujable.cpp
 *
 *  Created on: 2/5/2015
 *      Author: val
 */

#include "ArmaDibujable.h"

ArmaDibujable::ArmaDibujable() {
	// TODO Auto-generated constructor stub

}

ArmaDibujable::ArmaDibujable(Sprite* armaDib) {
	// TODO Auto-generated constructor stub
	armaDibujable = armaDib;
	estado = NO_VISIBLE;
}

void ArmaDibujable::dibujar(){
	armaDibujable->dibujar();
}

void ArmaDibujable::cambiarEstado(estado_objeto unEstado){
	this->estado = unEstado;
}

void ArmaDibujable::recibirNotificacion(Observable* unObservable){
	Arma* unArma = (Arma*) unObservable;
	Vector2f nueva_posicion = unArma->obtenerPosicionEnVentana();

	Vector2f posicion_final(nueva_posicion.X()*VentanaGrafica::Instance()->relacion_de_aspectoX(), nueva_posicion.Y()*VentanaGrafica::Instance()->relacion_de_aspectoY());

	//Actualizo la posicion del Sprite.
	this->armaDibujable->setPosicion(posicion_final);

	//Actualizo el estado del armaDibujable
	cambiarEstado(unArma->getEstado());
}

ArmaDibujable::~ArmaDibujable() {
	// TODO Auto-generated destructor stub
}

