/*
 * MapaDeCombos.cpp
 *
 *  Created on: 1/6/2015
 *      Author: val
 */

#include "MapaDeCombos.h"

#include <iostream>

MapaDeCombos::MapaDeCombos(vector<Combo*>* lista, int tolerancia, Uint32 tiempo_maximo_en_cola):
	combosJugador(lista), toleranciaDeError(tolerancia) {

	this->tiempo_inicio_combo = 0;
	this->tiempo_maximo_en_cola = tiempo_maximo_en_cola;
	this->colaDeEventos = new ColaEventos(LONGITUD_BUFFER);
}

void MapaDeCombos::agregar_tecla(string tecla){

	this->tiempo_inicio_combo = SDL_GetTicks();
	this->colaDeEventos->agregarEvento(tecla);
}

string MapaDeCombos::informar_combo(){

	for (size_t i = 0; i < this->combosJugador->size(); i++) {
		Combo* comboActual = (*this->combosJugador)[i];
		if (this->colaDeEventos->buscarCombo(comboActual, this->toleranciaDeError))
			return comboActual->getNombre();
	}

	return "COMBO_NO_ENCONTRADO";
}

void MapaDeCombos::update() {

	if (SDL_GetTicks() - this->tiempo_inicio_combo > this->tiempo_maximo_en_cola)
		this->colaDeEventos->clear();
}

void MapaDeCombos::imprimir() {
	/*
	vector<string> teclasActual (colaDeTeclas->begin(), colaDeTeclas->end());
	for (size_t i = 0; i < teclasActual.size(); i++)
		cout << teclasActual[i] << endl;
	*/
}

ColaEventos* MapaDeCombos::getColaDeEventos() {

	return this->colaDeEventos;
}

MapaDeCombos::~MapaDeCombos() {}

