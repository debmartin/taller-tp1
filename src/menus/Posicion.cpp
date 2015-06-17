/*
 * Posicion.cpp
 *
 *  Created on: 21/5/2015
 *      Author: ariel
 */

#include "Posicion.h"

#include <sstream>

Posicion::Posicion() {
	this->x = 0;
	this->y = 0;
}

Posicion::Posicion(int x, int y) {
	this->x = x;
	this->y = y;
	this->enfocado = false;
	this->elegido = false;
}

int Posicion::getX() const {
	return x;
}

int Posicion::getY() const {
	return y;
}

Posicion::~Posicion() {
	// TODO Auto-generated destructor stub
}

bool Posicion::estoyEnfocado() {
	return this->enfocado;
}

void Posicion::enfocar() {
	this->enfocado = true;
}

void Posicion::desenfocar() {
	this->enfocado = false;
}

ostream& operator <<(ostream &o, const Posicion &p) {

	string enfocadostring = "no";
	if ( p.enfocado )
		enfocadostring = "si";

	string elegidastring = "no";
	if ( p.elegido )
		elegidastring = "si";

	o<<"Posicion -> [y,x,enfocada,elegida]:["<<p.y<<","<<p.x<<","<<enfocadostring<<","<<elegidastring<<"]";
	return o;
}

string Posicion::toString() {
    ostringstream stream;
    stream <<*this;
	return stream.str();
}

bool Posicion::estoyElegido() {
	return this->elegido;
}

void Posicion::elegir() {
	this->elegido = true;
}

void Posicion::deselegir() {
	this->elegido = false;
}

void Posicion::posicionarIzquierda() {
	this->x = this->x - 1;
}

void Posicion::posicionarDerecha() {
	this->x = this->x + 1;
}

void Posicion::posicionarArriba() {
	this->y = this->y - 1;
}

void Posicion::posicionarAbajo() {
	this->y = this->y + 1;
}

bool Posicion::tieneMismasCoordenadasQue(Posicion* unaPosicion) {
	return ( this->x==unaPosicion->getX() && this->y==unaPosicion->getY() ) ;
}

void Posicion::setXY(int x, int y) {
	this->x = x;
	this->y = y;
}
