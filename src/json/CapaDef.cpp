/*
 * CapaDef.cpp
 *
 *  Created on: 9/4/2015
 *      Author: ariel-vm-barza
 */

#include "CapaDef.h"

#include <sstream>

#include "../utils/Logger.h"
#include "../utils/Util.h"


CapaDef::CapaDef() {
	this->imagen_fondo = "no_imagen";
	this->id_capa = "no_id";
	this->ancho = 0;
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

CapaDef::CapaDef(string imagen_fondo, string id, double ancho_in){
    if ( !Util::getInstancia()->existeArchivo(imagen_fondo) ) {
        imagen_fondo = IMAGEN_CAPA_DEFAULT;
        Logger::getInstance()->info("No existe la imagen de fondo para la capa "+imagen_fondo+". Por defecto se usa fondo_capa_defecto.png");
    }
    if (ancho_in <= 0)
        Logger::getInstance()->info("El ancho de la capa es negativo. Se elije un nuevo ancho igual al ancho del escenario");

	this->imagen_fondo = imagen_fondo;
	this->id_capa = id;
	this->ancho = (ancho_in > 0) ? ancho_in : ANCHO_CAPA_DEFAULT;
}

void CapaDef::ajustarAncho(double anchoEscenario, double anchoVentana){
    if (ancho > anchoEscenario) {
        ancho = anchoEscenario;
        Logger::getInstance()->info("El ancho de la capa es mayor al ancho del escenario. Se elije un nuevo ancho igual al ancho del escenario");
    }else if (ancho < anchoVentana) {
        ancho = anchoVentana;
        Logger::getInstance()->info("El ancho de la capa es menor al ancho del escenario. Se elije un nuevo ancho igual al ancho de la ventana");
    }
}

string CapaDef::toString() {
    ostringstream stream;
    stream <<*this;
	return stream.str();
}
