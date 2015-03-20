/*
 * Personaje.cpp
 *
 *  Created on: 19/3/2015
 *      Author: ariel
 */

#include "Personaje.h"


float Personaje::getAlto() const {
	return alto;
}

void Personaje::setAlto(float alto) {
	this->alto = alto;
}

float Personaje::getAncho() const {
	return ancho;
}

void Personaje::setAncho(float ancho) {
	this->ancho = ancho;
}

vector<string> Personaje::getSprites() const {
	return sprites;
}

void Personaje::setSprites(vector<string> sprites) {
	this->sprites = sprites;
}

int Personaje::getIndex() const {
	return z_index;
}

void Personaje::setIndex(int index) {
	z_index = index;
}

Personaje::~Personaje() {
	// TODO Auto-generated destructor stub
}

