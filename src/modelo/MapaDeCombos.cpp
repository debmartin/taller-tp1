/*
 * MapaDeCombos.cpp
 *
 *  Created on: 1/6/2015
 *      Author: val
 */

#include "MapaDeCombos.h"

#include <iostream>

MapaDeCombos::MapaDeCombos(vector<Combo*>* lista, int tolerancia):
	combosJugador(lista), toleranciaDeError(tolerancia) {
	colaDeTeclas = new deque<string>;
	comboActual = "";
	comboEfectuado = false;
}

void MapaDeCombos::agregar_tecla(string tecla){

	this->tiempo_inicio_combo = SDL_GetTicks();

	if (this->colaDeTeclas->size() >= LONGITUD_BUFFER)
		this->quitar_tecla();
	this->colaDeTeclas->push_back(tecla);
}

void MapaDeCombos::quitar_tecla(){
	this->colaDeTeclas->pop_front();
}

bool MapaDeCombos::combo_completado(){
	return comboEfectuado;
}

string MapaDeCombos::informar_combo(){

	if(comboEfectuado){
		comboEfectuado = false;
		return comboActual;
	}
	cout << "ERROR: MapaDeCombos::informar_combo()" << endl;
	return "ERROR";
}

void MapaDeCombos::update() {

	if (SDL_GetTicks() - this->tiempo_inicio_combo > TIEMPO_MAXIMO_EN_COLA)
		this->colaDeTeclas->clear();

}

bool comapararConCombo(vector<string> combo, vector<string> eventos, size_t tolerancia, int& cantidadEventosAQuitar) {

	size_t indiceCombo = 0;
	size_t coincidencias = 0;
	size_t discrepancias = 0;

	for (size_t k = 0; k < eventos.size(); k++) {
		if (eventos[k] == combo[0]) {
			indiceCombo = 0;
			coincidencias = 0;
			discrepancias = 0;

			for (size_t j = k; j < eventos.size(); j++) {
				if (eventos[j] == combo[indiceCombo]) {
					coincidencias++;
					indiceCombo++;
					if (coincidencias == combo.size())
						return true;
				}
				else {
					discrepancias++;
					if (discrepancias > tolerancia)
						break;
				}
			}
		}
	}

	return false;
}


void MapaDeCombos::buscarCombo() {
	// PARA TODOS LOS COMBOS DEL JUGADOR
	//cout << "---------------------" << endl;
	for (size_t i = 0; i < this->combosJugador->size(); i++) {
		// OBTENGO COMBO ACTUAL
		vector<string>* teclasCombo = (*this->combosJugador)[i]->verTeclas();

		// OBTENGO EVENTOS REALIZADOS POR EL USUARIO
		vector<string> teclasActual (colaDeTeclas->begin(), colaDeTeclas->end());

		// COMPARO
		//cout << "COMBO-ACTUAL-NOMBRE:" << (*this->combosJugador)[i]->getNombre() << endl;
		int cantidadEventosAQuitar = 0;
		bool comboEncontrado = comapararConCombo(*teclasCombo, teclasActual, this->toleranciaDeError, cantidadEventosAQuitar);//this->toleranciaDeError);
		if (comboEncontrado) {
			this->comboEfectuado = true;
			this->comboActual = (*this->combosJugador)[i]->getNombre();

			this->colaDeTeclas->clear();
			/*
			for (int veces = 0; veces < cantidadEventosAQuitar; veces ++)
				this->quitar_tecla();
				*/
		}
	}
}


void MapaDeCombos::imprimir() {
	vector<string> teclasActual (colaDeTeclas->begin(), colaDeTeclas->end());
	for (size_t i = 0; i < teclasActual.size(); i++)
		cout << teclasActual[i] << endl;
}

deque<string>* MapaDeCombos::getColaDeTeclas() {
	return this->colaDeTeclas;
}

MapaDeCombos::~MapaDeCombos() {
	// TODO Auto-generated destructor stub
}

