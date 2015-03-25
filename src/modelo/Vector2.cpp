/*
 * Vector2.cpp
 *
 *  Created on: 21/3/2015
 *      Author: val
 */
#include "Vector2.h"

Vector2::Vector2() {
	coordenada_x = 0;
	coordenada_y = 0;
}

void Vector2::setCoordenada(int x, int y) {
	this->coordenada_x = x;
	this->coordenada_y = y;
}

int Vector2::getCoordenadaX(){
	return this->coordenada_x;
}

int Vector2::getCoordenadaY(){
	return this->coordenada_y;
}

void Vector2::mover_en_X(int delta_x){
	this->coordenada_x += delta_x;
}

void Vector2::mover_en_Y(int delta_y){
	this->coordenada_y += delta_y;
}

Vector2::~Vector2() {
	// TODO Auto-generated destructor stub
}

