/*
 * Escenario.cpp
 *
 *  Created on: 19/3/2015
 *      Author: ariel
 */

#include "Escenario.h"

Escenario::Escenario() {
}

Escenario::Escenario(double ancho, double alto, double ypiso)
{
	this->ancho = ancho;
	this->alto = alto;
	this->ypiso = ypiso;
}

double Escenario::getAlto() const {
	return alto;
}

double Escenario::getAncho() const {
	return ancho;
}

double Escenario::getYpiso() const {
	return ypiso;
}

Escenario::~Escenario() {
	// TODO Auto-generated destructor stub
}

ostream& operator <<(ostream &o, const Escenario &e) {

        o<<"escenario -> [ancho, alto, ypiso]=["<<e.ancho<<", "<<e.alto<<", "<<e.ypiso<<"]";
        return o;
}
