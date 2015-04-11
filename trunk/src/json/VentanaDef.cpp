/*
 * VentanaDef.cpp
 *
 *  Created on: 9/4/2015
 *      Author: ariel-vm-barza
 */

#include "VentanaDef.h"

VentanaDef::VentanaDef() {
}

VentanaDef::VentanaDef(int ancho_px, int alto_px, double ancho, double margen_x)
{
	this->ancho_px = ancho_px;
	this->alto_px = alto_px;
	this->ancho = ancho;
	this->margen_x = margen_x;
}

int VentanaDef::getAltoPx() const {
	return alto_px;
}

double VentanaDef::getAncho() const {
	return ancho;
}

int VentanaDef::getAnchoPx() const {
	return ancho_px;
}

VentanaDef::~VentanaDef() {
	// TODO Auto-generated destructor stub
}

double VentanaDef::getMargenX() const {
	return margen_x;
}

ostream& operator <<(ostream &o, const VentanaDef &v) {

        o<<"VentanaDef -> [anchopx, altopx, ancho, margen_x]=["<<v.ancho_px<<", "<<v.alto_px<<", "<<v.ancho<<", "<<v.margen_x<<"]";

        return o;
}
