/*
 * MapaDeCombos.cpp
 *
 *  Created on: 1/6/2015
 *      Author: val
 */

#include "MapaDeCombos.h"

MapaDeCombos::MapaDeCombos(vector<Combo*>* lista, int tolerancia):
	combosJugador(lista), toleranciaDeError(tolerancia) {
	colaDeTeclas = new deque<string>;
	comboActual = NULL;
}

void MapaDeCombos::agregar_tecla(string tecla){
	this->colaDeTeclas->push_front(tecla);
}

void MapaDeCombos::quitar_tecla(){
	this->colaDeTeclas->pop_back();
}

bool MapaDeCombos::combo_completado(){
	return (comboActual != NULL);
}

int MapaDeCombos::informar_combo(){
	return comboActual->getNumero();
}

bool comapararConCombo(vector<string> teclasCombo, vector<string> teclasActual, int tolerancia) {
	return true;
}

void MapaDeCombos::buscarCombo() {
	for (int i = 0; i < this->combosJugador->size(); i++) {
		vector<string>* teclasCombo = (*this->combosJugador)[i]->verTeclas();
		vector<string> teclasActual (colaDeTeclas->begin(), colaDeTeclas->end());

		comapararConCombo(*teclasCombo, teclasActual, this->toleranciaDeError);
	}
}

MapaDeCombos::~MapaDeCombos() {
	// TODO Auto-generated destructor stub
}

