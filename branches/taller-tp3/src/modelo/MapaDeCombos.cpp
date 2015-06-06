/*
 * MapaDeCombos.cpp
 *
 *  Created on: 1/6/2015
 *      Author: val
 */

#include "MapaDeCombos.h"

MapaDeCombos::MapaDeCombos(list<Combo*>* lista1, list<Combo*>* lista2, int tolerancia):
	combosJugador1(lista1), combosJugador2(lista2), toleranciaDeError(tolerancia){
	comboActual = NULL;
}

void MapaDeCombos::manejar_evento(SDL_Event &evento){

}

bool MapaDeCombos::combo_completado(){
	return (comboActual != NULL);
}

int MapaDeCombos::informar_combo(){
	return comboActual->getNumero();
}

MapaDeCombos::~MapaDeCombos() {
	// TODO Auto-generated destructor stub
}

