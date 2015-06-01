/*
 * Combo.cpp
 *
 *  Created on: 1/6/2015
 *      Author: val
 */

#include "Combo.h"

Combo::Combo(map<string, int>* teclas, string nombre):
	mapaDeTeclas(teclas), nombreCombo(nombre){
}

Combo::~Combo() {
	// TODO Auto-generated destructor stub
}

string Combo::getNombre(){
	return nombreCombo;
}
