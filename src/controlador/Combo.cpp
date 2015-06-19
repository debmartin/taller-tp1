/*
 * Combo.cpp
 *
 *  Created on: 1/6/2015
 *      Author: val
 */

#include "Combo.h"

Combo::Combo(vector<string>* teclas, string nombre, int num):
	teclas(teclas), nombreCombo(nombre), numeroCombo(num){
}

Combo::~Combo() {
	// TODO Auto-generated destructor stub
}

string Combo::getNombre(){
	return nombreCombo;
}

int Combo::getNumero(){
	return numeroCombo;
}

vector<string>* Combo::verTeclas(){
	return this->teclas;
}
