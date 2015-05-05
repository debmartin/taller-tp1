/*
 * Arma.cpp
 *
 *  Created on: 2/5/2015
 *      Author: val
 */

#include "Arma.h"

Arma::Arma() {
	// TODO Auto-generated constructor stub
	this->posicion = POS_INICIAL_OBJETO;
	this->trayectoria = new MRU(POS_INICIAL_OBJETO, VELOCIDAD_OBJETO);
	this->damage = DANIO_ARMA;
	this->estado = NO_VISIBLE;
}

int Arma::quitarEnergia(){
	return this->damage;
}

void Arma::posicionar(Vector2f pos){
	posicion = pos;
}

void Arma::cambiarEstado(estado_objeto unEstado){
	this->estado = unEstado;
}

estado_objeto Arma::getEstado(){
	return this->estado;
}

void Arma::update(){
	float tActual = ((float)(SDL_GetTicks())/1000.0f) - tCreacion;
	posicion = this->trayectoria->getPosicion(tActual);
}

void Arma::agregarObservador(Observador* unObservador){
	Observable::agregarObservador(unObservador);
}

void Arma::notificarObservadores(){
	Observable::notificarObservadores();
}

Vector2f Arma::obtenerPosicionEnVentana(){
	Vector2f P1(posicion.X(), posicion.Y());
	//Vector2f P1(posicion.X(), posicion.Y() + getAlto());
	Vector2f P2 = VentanaGrafica::Instance()->calcularPosicionEnVentana(P1);
	return P2;
}

Arma::~Arma() {
	// TODO Auto-generated destructor stub
}

