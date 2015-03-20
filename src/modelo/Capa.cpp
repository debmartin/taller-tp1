/*
 * Capa.cpp
 *
 *  Created on: 19/3/2015
 *      Author: ariel
 */

#include "Capa.h"

float Capa::getAncho() const {
	return ancho;
}

void Capa::setAncho(float ancho) {
	this->ancho = ancho;
}

string Capa::getImagenFondo() const {
	return imagen_fondo;
}

void Capa::setImagenFondo(string imagenFondo) {
	imagen_fondo = imagenFondo;
}

Capa::~Capa() {
	// TODO Auto-generated destructor stub
}

