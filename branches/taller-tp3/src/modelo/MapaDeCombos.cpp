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
}

bool comapararConCombo(vector<string> combo, vector<string> eventos, size_t tolerancia, int& cantidadEventosAQuitar) {

	// LA CANTIDAD DE EVENTOS SIEMPRE DEBE SER MAYOR O IGUAL AL TAMANIO DEL COMBO
	if (combo.size() > eventos.size())
		return false;

	// LA TOLERANCIA NO PUEDE SER MAYOR AL TAMANIO DEL COMBO
	if (tolerancia > combo.size())
		tolerancia = combo.size();

	size_t cantidadCoincidenciasEncontradas = 0;

	for (size_t i = 0;  i <= (eventos.size() - combo.size()); i++) { // RECORRO EVENTO

		cantidadCoincidenciasEncontradas = 0;

		for (size_t k = i; k < (i + combo.size()); k++) { // RECORRO SUB-EVENTOS

			if (eventos[k] == combo[k-i])
				cantidadCoincidenciasEncontradas++;
		}

		if ((combo.size() - cantidadCoincidenciasEncontradas) <= tolerancia) {
			cantidadEventosAQuitar = i + combo.size();
			return true;
		}
	}
	return false;
}


void MapaDeCombos::buscarCombo() {
	cout << "111" << endl;
	// PARA TODOS LOS COMBOS DEL JUGADOR
	for (size_t i = 0; i < this->combosJugador->size(); i++) {
		// OBTENGO COMBO ACTUAL
		vector<string>* teclasCombo = (*this->combosJugador)[i]->verTeclas();

		// OBTENGO EVENTOS REALIZADOS POR EL USUARIO
		vector<string> teclasActual (colaDeTeclas->begin(), colaDeTeclas->end());

		// COMPARO
		cout << "COMBO-ACTUAL-NOMBRE:" << (*this->combosJugador)[i]->getNombre() << endl;
		int cantidadEventosAQuitar = 0;
		bool comboEncontrado = comapararConCombo(*teclasCombo, teclasActual, 0, cantidadEventosAQuitar);//this->toleranciaDeError);
		if (comboEncontrado) {
			this->comboEfectuado = true;
			this->comboActual = (*this->combosJugador)[i]->getNombre();
			for (int veces = 0; veces < cantidadEventosAQuitar; veces ++)
				this->quitar_tecla();
		}
	}
}


void MapaDeCombos::imprimir() {
	cout << "---------------------------------" << endl;
	vector<string> teclasActual (colaDeTeclas->begin(), colaDeTeclas->end());
	for (size_t i = 0; i < teclasActual.size(); i++)
		cout << teclasActual[i] << endl;
}

MapaDeCombos::~MapaDeCombos() {
	// TODO Auto-generated destructor stub
}

