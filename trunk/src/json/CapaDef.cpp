/*
 * CapaDef.cpp
 *
 *  Created on: 9/4/2015
 *      Author: ariel-vm-barza
 */

#include "CapaDef.h"

CapaDef::CapaDef() {
}

double CapaDef::getAncho() const {
	return ancho;
}

string CapaDef::getImagenFondo() const {
	return imagen_fondo;
}

CapaDef::~CapaDef() {
	// TODO Auto-generated destructor stub
}

ostream& operator <<(ostream &o, const CapaDef &c) {

        o<<"CapaDef -> [imagen_fondo, ancho]=["<<c.imagen_fondo<<", "<<c.ancho<<"]";
        return o;
}

CapaDef::CapaDef(string imagen_fondo, double ancho){
	this->imagen_fondo = imagen_fondo;
	this->ancho = ancho;
}
