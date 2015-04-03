/*
 * Ventana.cpp
 *
 *  Created on: 19/3/2015
 *      Author: ariel
 */

#include "Ventana.h"

Ventana::Ventana() {
}

Ventana::Ventana(int ancho_px, int alto_px, double ancho)
{
	this->ancho_px = ancho_px;
	this->alto_px = alto_px;
	this->ancho = ancho;
}

int Ventana::getAltoPx() const {
	return alto_px;
}

double Ventana::getAncho() const {
	return ancho;
}

int Ventana::getAnchoPx() const {
	return ancho_px;
}

Ventana::~Ventana() {
	// TODO Auto-generated destructor stub
}

ostream& operator <<(ostream &o, const Ventana &v) {

        o<<"ventana -> [anchopx, altopx, ancho]=["<<v.ancho_px<<", "<<v.alto_px<<", "<<v.ancho<<"]";

        return o;
}

