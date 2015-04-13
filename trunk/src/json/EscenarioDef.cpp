/*
 * EscenarioDef.cpp
 *
 *  Created on: 9/4/2015
 *      Author: ariel-vm-barza
 */

#include "EscenarioDef.h"

EscenarioDef::EscenarioDef() {
}

EscenarioDef::EscenarioDef(double ancho, double alto, double ypiso)
{
	this->ancho = ancho;
	this->alto = alto;
	this->ypiso = ypiso;
}

double EscenarioDef::getAlto() const {
	return alto;
}

double EscenarioDef::getAncho() const {
	return ancho;
}

double EscenarioDef::getYpiso() const {
	return ypiso;
}

EscenarioDef::~EscenarioDef() {
	// TODO Auto-generated destructor stub
}

ostream& operator <<(ostream &o, const EscenarioDef &e) {

        o<<"EscenarioDef -> [ancho, alto, ypiso]=["<<e.ancho<<", "<<e.alto<<", "<<e.ypiso<<"]";
        return o;
}
