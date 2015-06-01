/*
 * MapaDeCombos.cpp
 *
 *  Created on: 1/6/2015
 *      Author: val
 */

#include "MapaDeCombos.h"

MapaDeCombos::MapaDeCombos(list<Combo*>* lista1, list<Combo*>* lista2, int tolerancia):
	combosJugador1(lista1), combosJugador2(lista2), toleranciaDeError(tolerancia){
}

MapaDeCombos::~MapaDeCombos() {
	// TODO Auto-generated destructor stub
}

