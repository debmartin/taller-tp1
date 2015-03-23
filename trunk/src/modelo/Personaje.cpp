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

Coordenada Personaje::getPosicion(){
	return this->unaCoordenada;
}

void Personaje::setVida(int cantidad){
	this->vida += cantidad;
}

int Personaje::getVida(){
	return this->vida;
}

void Personaje::caminarDerecha(){
	//Valido que no camine fuera del escenario
	if((this->unaCoordenada.getCoordenadaX() + this->ancho) < ANCHO_ESCENARIO){
		this->unaCoordenada.mover_en_X(this->velocidad);
	}
}

void Personaje::caminarIzquierda(){
	//Valido que no camine fuera del escenario
	if(this->unaCoordenada.getCoordenadaX() > 0){
		this->unaCoordenada.mover_en_X(-this->velocidad);
	}
}
void Personaje::moverArriba(){
	//Valido que no camine fuera del escenario
	if((this->unaCoordenada.getCoordenadaY() + this->alto) < ALTO_ESCENARIO){
		this->unaCoordenada.mover_en_Y(this->velocidad);
	}
}

void Personaje::moverAbajo(){
	//Valido que no camine fuera del escenario
	if(this->unaCoordenada.getCoordenadaY() > 0){
		this->unaCoordenada.mover_en_Y(-this->velocidad);
	}
}

Personaje::~Personaje(){
	// TODO Auto-generated destructor stub
}

