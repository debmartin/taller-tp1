/*
 * Ventana.cpp
 *
 *  Created on: 19/3/2015
 *      Author: ariel
 */

#include "Ventana.h"

int Ventana::getAltoPx() const {
	return alto_px;
}

void Ventana::setAltoPx(int altoPx) {
	alto_px = altoPx;
}

float Ventana::getAncho() const {
	return ancho;
}

void Ventana::setAncho(float ancho) {
	this->ancho = ancho;
}

int Ventana::getAnchoPx() const {
	return ancho_px;
}

void Ventana::setAnchoPx(int anchoPx) {
	ancho_px = anchoPx;
}

Ventana::~Ventana() {
	// TODO Auto-generated destructor stub
}

