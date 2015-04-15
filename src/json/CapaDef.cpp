/*
 * CapaDef.cpp
 *
 *  Created on: 9/4/2015
 *      Author: ariel-vm-barza
 */

#include "CapaDef.h"
#include "../utils/Util.h"

CapaDef::CapaDef() {
}

double CapaDef::getAncho() const {
	return ancho;
}

string CapaDef::getImagenFondo() const {
	return imagen_fondo;
}

string CapaDef::getIdCapa() const {
	return id_capa;
}

CapaDef::~CapaDef() {
	// TODO Auto-generated destructor stub
}

ostream& operator <<(ostream &o, const CapaDef &c) {

        o<<"CapaDef -> [imagen_fondo, ancho]=["<<c.imagen_fondo<<", "<<c.ancho<<"]";
        return o;
}

CapaDef::CapaDef(string imagen_fondo, string id, double ancho){
	this->imagen_fondo = imagen_fondo;
	this->id_capa = id;
	this->ancho = ancho;
//	if ( !Util::getInstancia()->existeArchivo(imagen_fondo) )
//        throw exception();
//    if (ancho <= 0)
//        throw exception();
}
