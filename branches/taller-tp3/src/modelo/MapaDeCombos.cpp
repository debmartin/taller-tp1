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

bool comapararConCombo(vector<string> teclasCombo, vector<string> teclasActual, int tolerancia) {
	return true;
}

void MapaDeCombos::buscarCombo() {
	/*
	for (int i = 0; i < this->combosJugador->size(); i++) {
		vector<string>* teclasCombo = (*this->combosJugador)[i]->verTeclas();
		vector<string> teclasActual (colaDeTeclas->begin(), colaDeTeclas->end());

		comapararConCombo(*teclasCombo, teclasActual, this->toleranciaDeError);
	}
	*/
	//this->comboEfectuado = true;
	//this->comboActual = "SONYA_PODER";
}


void MapaDeCombos::imprimir() {
	cout << "---------------------------------" << endl;
	vector<string> teclasActual (colaDeTeclas->begin(), colaDeTeclas->end());
	for (int i = 0; i < teclasActual.size(); i++)
		cout << teclasActual[i] << endl;
}

MapaDeCombos::~MapaDeCombos() {
	// TODO Auto-generated destructor stub
}

