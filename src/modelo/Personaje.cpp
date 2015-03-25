/*
 * Personaje.cpp
 *
 *  Created on: 19/3/2015
 *      Author: ariel
 */

#include "Personaje.h"

#define ANCHO_ESCENARIO 600

Personaje::Personaje() {
}

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

int Personaje::getZindex() const {
	return z_index;
}

void Personaje::setZindex(int z_index) {
	this->z_index = z_index;
}

void Personaje::setLimiteSuperior(int limite){
	this->limite_superior = limite;
}

int Personaje::getLimiteSuperior(){
	return this->limite_superior;
}

void Personaje::setLimiteInferior(int limite){
	this->limite_inferior = limite;
}

int Personaje::getLimiteInferior(){
	return this->limite_inferior;
}

void Personaje::setLimiteDerecho(int limite){
	this->limite_derecho = limite;
}

int Personaje::getLimiteDerecho(){
	return this->limite_derecho;
}

void Personaje::setLimiteIzquierdo(int limite){
	this->limite_izquierdo = limite;
}

int Personaje::getLimiteIzquierdo(){
	return this->limite_izquierdo;
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
	if((this->unaCoordenada.getCoordenadaX() > this->limite_izquierdo) && (this->unaCoordenada.getCoordenadaX() + this->ancho) < this->limite_derecho){
		this->unaCoordenada.mover_en_X(this->velocidad.getCoordenadaX());
	}
	//Valido que no camine fuera del escenario en Y
	if((this->unaCoordenada.getCoordenadaY() > this->limite_inferior) && (this->unaCoordenada.getCoordenadaY() + this->alto) < this->limite_superior){
		this->unaCoordenada.mover_en_Y(this->velocidad.getCoordenadaY());
	}
}

Personaje::~Personaje(){
	// TODO Auto-generated destructor stub
}

