/*
 * MapaDeCombos.cpp
 *
 *  Created on: 1/6/2015
 *      Author: val
 */

#include "MapaDeCombos.h"

MapaDeCombos::MapaDeCombos(list<Combo*>* lista1, list<Combo*>* lista2, int tolerancia):
	combosJugador1(lista1), combosJugador2(lista2), toleranciaDeError(tolerancia){
	colaDeEventosPersonaje1 = new queue<string>;
	colaDeEventosPersonaje2 = new queue<string>;
	comboActual = NULL;
}

void MapaDeCombos::agregar_tecla(string tecla, int numeroPersonaje){
	if(numeroPersonaje == 0){
		this->colaDeEventosPersonaje1->push(tecla);
	}else{
		this->colaDeEventosPersonaje2->push(tecla);
	}
}

void MapaDeCombos::quitar_tecla(int numeroPersonaje){
	if(numeroPersonaje == 0){
		this->colaDeEventosPersonaje1->pop();
	}else{
		this->colaDeEventosPersonaje2->pop();
	}
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

