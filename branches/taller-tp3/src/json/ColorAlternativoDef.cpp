/*
 * ColorAlternativoDef.cpp
 *
 *  Created on: 30/4/2015
 *      Author: ariel
 */

#include "ColorAlternativoDef.h"

#include <sstream>

ColorAlternativoDef::ColorAlternativoDef() {
	this->hinicial = -10;
	this->hfinal = 10;
	this->desplazamiento = 30;
}

ColorAlternativoDef::ColorAlternativoDef(double hinicial, double hfinal, double desplazamiento) {
	this->hinicial = hinicial;
	this->hfinal = hfinal;
	this->desplazamiento = desplazamiento;
}

double ColorAlternativoDef::getDesplazamiento() const {
	return desplazamiento;
}

void ColorAlternativoDef::setDesplazamiento(double desplazamiento) {
	this->desplazamiento = desplazamiento;
}

double ColorAlternativoDef::getHfinal() const {
	return hfinal;
}

void ColorAlternativoDef::setHfinal(double hfinal) {
	this->hfinal = hfinal;
}

double ColorAlternativoDef::getHinicial() const {
	return hinicial;
}

void ColorAlternativoDef::setHinicial(double hinicial) {
	this->hinicial = hinicial;
}

ColorAlternativoDef::~ColorAlternativoDef() {
	// TODO Auto-generated destructor stub
}


ostream& operator <<(ostream &o, const ColorAlternativoDef &c) {

        o<<"ColorAlternativoDef -> [hinicial, hfinal, desplaz]=[";
        o<<c.hinicial<<", "<<c.hfinal<<", "<<c.desplazamiento<<"]";
        return o;
}


string ColorAlternativoDef::toString() {
    ostringstream stream;
    stream <<*this;
	return stream.str();
}
