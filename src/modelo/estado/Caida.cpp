/*
 * Caida.cpp
 *
 *  Created on: 23/5/2015
 *      Author: val
 */

#include "Caida.h"

Caida::Caida(Trayectoria* trayectoriaActual, float tiempoDeCreacion, BVH* caja) :
	Estado(trayectoriaActual, tiempoDeCreacion, RECIBIENDO_GOLPE_CAIDA, caja) {
}

Caida::~Caida() {
	// TODO Auto-generated destructor stub
}

