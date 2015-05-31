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
							orientacion,
							SPR_ABAJO_CENTRO);

	armaDibujable->escalarConTamanio(tamanioPx.X(), tamanioPx.Y());
	estado = NO_VISIBLE;

	// ENVOLVENTE
	    this->animacionEnvolvente = new Animacion(Renderizador::Instance()->getRenderer(), "DEFAULT/ENVOLVENTE.png", 1, 1, "ENVOLVENTE");
	    this->spriteEnvolvente = new Sprite(this->animacionEnvolvente, Renderizador::Instance()->getRenderer(), posicionIni, orientacion, SPR_ABAJO_IZQUIERDA);
}

void ArmaDibujable::dibujar(){
	if(estado == VISIBLE){
		armaDibujable->dibujar();
		this->spriteEnvolvente->dibujar();
	}
}

void ArmaDibujable::actualizar(){
	armaDibujable->update();
	this->spriteEnvolvente->update();
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

	// ENVOLVENTE
	float anchoPx = unArma->obtenerCajaColision()->calcularAnchoEnvolvente() * VentanaGrafica::Instance()->relacion_de_aspectoX();
	float altoPx  = unArma->obtenerCajaColision()->calcularAltoEnvolvente()  * VentanaGrafica::Instance()->relacion_de_aspectoY();
	this->spriteEnvolvente->escalarConTamanio(anchoPx, altoPx);

	Vector2f posicion_abajo_izquierda_logica_en_escenario =
			unArma->obtenerCajaColision()->calcularPosicion();
	//cout << "ABAJO_IZQUIERDA:" << posicion_abajo_izquierda_logica_en_escenario << endl;
	Vector2f posicion_abajo_izquierda_logica_en_ventana =
			VentanaGrafica::Instance()->calcularPosicionEnVentana(posicion_abajo_izquierda_logica_en_escenario);

	Vector2f posicion_abajo_izquierda_px_en_ventana = Vector2f(
			posicion_abajo_izquierda_logica_en_ventana.X() * VentanaGrafica::Instance()->relacion_de_aspectoX(),
			posicion_abajo_izquierda_logica_en_ventana.Y() * VentanaGrafica::Instance()->relacion_de_aspectoY());

	this->spriteEnvolvente->setPosicion(posicion_abajo_izquierda_px_en_ventana);
}

ArmaDibujable::~ArmaDibujable() {
	delete this->armaDibujable;
	delete this->spriteEnvolvente;
}

