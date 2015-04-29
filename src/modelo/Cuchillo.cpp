/*
 * Cuchillo.cpp
 *
 *  Created on: 28/4/2015
 *      Author: val
 */

#include "Cuchillo.h"

Cuchillo::Cuchillo() {
	// TODO Auto-generated constructor stub
	this->posicion = POS_INICIAL_OBJETO;
	this->trayectoria = new MRU(POS_INICIAL_OBJETO, VELOCIDAD_OBJETO);
	this->damage = DANIO_CUCHILLO;
}

int Cuchillo::quitarEnergia(){
	return this->damage;
}

void Cuchillo::posicionar(Vector2f pos){
	posicion = pos;
}

void Cuchillo::update(){
	float tActual = ((float)(SDL_GetTicks())/1000.0f) - tCreacion;
	posicion = this->trayectoria->getPosicion(tActual);
}

Cuchillo::~Cuchillo() {
	// TODO Auto-generated destructor stub
}

