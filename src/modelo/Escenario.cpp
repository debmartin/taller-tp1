/*
 * Escenario.cpp
 *
 *  Created on: 19/3/2015
 *      Author: ariel
 */

#include "Escenario.h"

Escenario::Escenario() {
}

double Escenario::getAlto() const {
	return alto;
}

void Escenario::setAlto(double alto) {
	this->alto = alto;
}

double Escenario::getAncho() const {
	return ancho;
}

void Escenario::setAncho(double ancho) {
	this->ancho = ancho;
}

int Escenario::getYpiso() const {
	return ypiso;
}

void Escenario::setYpiso(int ypiso) {
	this->ypiso = ypiso;
}

Escenario::~Escenario() {
	// TODO Auto-generated destructor stub
}

ostream& operator <<(ostream &o, const Escenario &e) {

        o<<"escenario -> [ancho, alto, ypiso]=["<<e.ancho<<", "<<e.alto<<", "<<e.ypiso<<"]";
        return o;
}
