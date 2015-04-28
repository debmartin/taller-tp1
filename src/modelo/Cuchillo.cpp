/*
 * Cuchillo.cpp
 *
 *  Created on: 28/4/2015
 *      Author: val
 */

#include "Cuchillo.h"

Cuchillo::Cuchillo(Vector2f posicion) {
	// TODO Auto-generated constructor stub
	this->trayectoria = new MRU(posicion, VELOCIDAD_OBJETO);
	this->damage = DANIO_CUCHILLO;
}

int Cuchillo::quitarEnergia(){
	return this->damage;
}

Cuchillo::~Cuchillo() {
	// TODO Auto-generated destructor stub
}

