/*
 * Coordenada.cpp
 *
 *  Created on: 21/3/2015
 *      Author: val
 */
#include "Coordenada.h"

void Coordenada::setCoordenada(int x, int y) {
	this->coordenada_x = x;
	this->coordenada_y = y;
}

int Coordenada::getCoordenadaX(){
	return this->coordenada_x;
}

int Coordenada::getCoordenadaY(){
	return this->coordenada_y;
}

void Coordenada::mover_en_X(int delta_x){
	this->coordenada_x += delta_x;
}

void Coordenada::mover_en_Y(int delta_y){
	this->coordenada_y += delta_y;
}

Coordenada::~Coordenada() {
	// TODO Auto-generated destructor stub
}
