/*
 * Escenario.cpp
 *
 *  Created on: 19/3/2015
 *      Author: ariel
 */

#include "Escenario.h"

float Escenario::getAlto() const {
	return alto;
}

void Escenario::setAlto(float alto) {
	this->alto = alto;
}

float Escenario::getAncho() const {
	return ancho;
}

void Escenario::setAncho(float ancho) {
	this->ancho = ancho;
}

int Escenario::getPiso() const {
	return y_piso;
}

void Escenario::setPiso(int piso) {
	y_piso = piso;
}

Escenario::~Escenario() {
	// TODO Auto-generated destructor stub
}

