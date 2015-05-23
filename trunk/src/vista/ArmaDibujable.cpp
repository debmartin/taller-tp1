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

ArmaDibujable::ArmaDibujable(Animacion* animIni, Vector2f posicionIni, Vector2f tamanioPx, OrientacionSprite orientacion) {
	// TODO Auto-generated constructor stub
	armaDibujable = new Sprite(
							animIni,
							Renderizador::Instance()->getRenderer(),
							posicionIni,
							orientacion);

	armaDibujable->escalarConTamanio(tamanioPx.X(), tamanioPx.Y());
	estado = NO_VISIBLE;
}

void ArmaDibujable::dibujar(){
	if(estado == VISIBLE){
		armaDibujable->dibujar();
	}
}

void ArmaDibujable::actualizar(){
	armaDibujable->update();
}

void ArmaDibujable::cambiarEstado(estado_objeto unEstado){
	this->estado = unEstado;
}

Sprite* ArmaDibujable::getSprite(){
	return armaDibujable;
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

