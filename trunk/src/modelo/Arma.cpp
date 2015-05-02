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
}

int Arma::quitarEnergia(){
	return this->damage;
}

void Arma::posicionar(Vector2f pos){
	posicion = pos;
}

void Arma::update(){
	float tActual = ((float)(SDL_GetTicks())/1000.0f) - tCreacion;
	posicion = this->trayectoria->getPosicion(tActual);
}

Arma::~Arma() {
	// TODO Auto-generated destructor stub
}

