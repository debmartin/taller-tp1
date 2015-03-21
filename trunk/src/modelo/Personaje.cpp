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

void Personaje::setPosicion(int x, int y) {
	this->coordenada_x = x;
	this->coordenada_y = y;
}

void Personaje::moverse(int delta_x, int delta_y){
	this->coordenada_x += delta_x;
	this->coordenada_y += delta_y;
}

void Personaje::saltar(){

}

Personaje::~Personaje() {
	// TODO Auto-generated destructor stub
}

