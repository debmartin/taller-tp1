/*
 * Escenario.cpp
 *
 *  Created on: 19/3/2015
 *      Author: ariel
 */

#include "Escenario.h"

Escenario::Escenario() {
}

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

int Escenario::getYpiso() const {
	return ypiso;
}

void Escenario::setYpiso(int ypiso) {
	this->ypiso = ypiso;
}

Escenario::~Escenario() {
	// TODO Auto-generated destructor stub
}

