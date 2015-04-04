/*
 * Capa.cpp
 *
 *  Created on: 19/3/2015
 *      Author: ariel
 */

#include "Capa.h"

Capa::Capa() {
}

double Capa::getAncho() const {
	return ancho;
}

string Capa::getImagenFondo() const {
	return imagen_fondo;
}

Capa::~Capa() {
	// TODO Auto-generated destructor stub
}

ostream& operator <<(ostream &o, const Capa &c) {

        o<<"capa -> [imagen_fondo, ancho]=["<<c.imagen_fondo<<", "<<c.ancho<<"]";
        return o;
}

Capa::Capa(string imagen_fondo, double ancho){
	this->imagen_fondo = imagen_fondo;
	this->ancho = ancho;
}
