/*
 * EscenarioDef.cpp
 *
 *  Created on: 9/4/2015
 *      Author: ariel-vm-barza
 */

#include "EscenarioDef.h"

#include <sstream>
#include <string>

#define ANCHO_DEFAULT 1200

EscenarioDef::EscenarioDef() {
	this->ancho = 0;
	this->alto = 0;
	this->ypiso = 0;
}

EscenarioDef::EscenarioDef(double anchoIn, double altoIn, double ypisoIn)
{
    if (anchoIn <= 0)
        Logger::getInstance()->info("El ancho del escenario es negativo. Se elije uno nuevo: 1200");
    if (altoIn <= 0)
        Logger::getInstance()->info("El alto del escenario es negativo. Se elije uno nuevo: 800");
    if (ypisoIn < 0)
        Logger::getInstance()->info("El y del piso del personaje es negativo. Se elije uno nuevo con el valor de cero");

	this->ancho = (anchoIn > 0) ? anchoIn : ANCHO_ESC_DEFAULT;
	this->alto = (altoIn > 0) ? altoIn : ALTO_ESC_DEFAULT;
	this->ypiso = (ypisoIn >= 0) ? ypisoIn : Y_PISO_ESC_DEFAULT;
}

void EscenarioDef::ajustarYPiso(double altoPersonaje){
    if ((alto - ypiso) < altoPersonaje) {
        ypiso = Y_PISO_ESC_DEFAULT;
        Logger::getInstance()->info("El y del piso del personaje sobrepasa al escenario con respecto a su altura. Se elije uno nuevo con el valor de cero");
    }
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

string EscenarioDef::toString() {
    ostringstream stream;
    stream <<*this;
	return stream.str();
}
