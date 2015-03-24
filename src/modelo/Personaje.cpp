/*
 * Personaje.cpp
 *
 *  Created on: 19/3/2015
 *      Author: ariel
 */

#include "Personaje.h"

#define ANCHO_ESCENARIO 600

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
	this->unaCoordenada.setCoordenada(x,y);
}

Vector2 Personaje::getPosicion(){
	return this->unaCoordenada;
}

void Personaje::setEstado(int unEstado){
	this->estado = unEstado;
}

int Personaje::getEstado(){
	return this->estado;
}

void Personaje::setVida(int cantidad){
	this->vida += cantidad;
}

int Personaje::getVida(){
	return this->vida;
}

void Personaje::aumentar_velocidadX(){
	this->velocidad.mover_en_X(DELTA_PASO);
}

void Personaje::disminuir_velocidadX(){
	this->velocidad.mover_en_X(-DELTA_PASO);
}

void Personaje::aumentar_velocidadY(){
	this->velocidad.mover_en_X(DELTA_PASO);
}

void Personaje::disminuir_velocidadY(){
	this->velocidad.mover_en_X(-DELTA_PASO);
}

void Personaje::mover(){
	//Valido que no camine fuera del escenario en X
	if((this->unaCoordenada.getCoordenadaX() > 0) && (this->unaCoordenada.getCoordenadaX() + this->ancho) < ANCHO_ESCENARIO){
		this->unaCoordenada.mover_en_X(this->velocidad.getCoordenadaX());
	}
	//Valido que no camine fuera del escenario en Y
	if((this->unaCoordenada.getCoordenadaY() > 0) && (this->unaCoordenada.getCoordenadaY() + this->alto) < ALTO_ESCENARIO){
		this->unaCoordenada.mover_en_Y(this->velocidad.getCoordenadaY());
	}
}

Personaje::~Personaje(){
	// TODO Auto-generated destructor stub
}

