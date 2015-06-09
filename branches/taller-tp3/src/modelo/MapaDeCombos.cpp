/*
 * MapaDeCombos.cpp
 *
 *  Created on: 1/6/2015
 *      Author: val
 */

#include "MapaDeCombos.h"

MapaDeCombos::MapaDeCombos(vector<Combo*>* lista, int tolerancia):
	combosJugador(lista), toleranciaDeError(tolerancia){
	colaDeTeclas = new queue<string>;
	comboActual = NULL;
}

void MapaDeCombos::agregar_tecla(string tecla){
	this->colaDeTeclas->push(tecla);
}

void MapaDeCombos::quitar_tecla(){
	this->colaDeTeclas->pop();
}

bool MapaDeCombos::combo_completado(){
	return (comboActual != NULL);
}

int MapaDeCombos::informar_combo(){
	return comboActual->getNumero();
}

void MapaDeCombos::buscarCombo() {

}
MapaDeCombos::~MapaDeCombos() {
	// TODO Auto-generated destructor stub
}

