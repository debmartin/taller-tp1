/*
 * VentanaDef.cpp
 *
 *  Created on: 9/4/2015
 *      Author: ariel-vm-barza
 */

#include "VentanaDef.h"

#include <sstream>
#include <string>

VentanaDef::VentanaDef() {
	this->ancho_px = 0;
	this->alto_px = 0;
	this->ancho = 0;
}

VentanaDef::VentanaDef(int ancho_px_in, int alto_px_in, double ancho_in)
{
    if ( ancho_px_in <= 0 )
		Logger::getInstance()->info("El ancho en pixeles de la ventana es negativa. Se elije uno nuevo: 800");
	if ( alto_px_in <= 0 )
		Logger::getInstance()->info("El alto en pixeles de la ventana es negativa. Se elije uno nuevo: 600");

	this->ancho_px = (ancho_px_in > 0) ? ancho_px_in : ANCHOPX_VENTANA_DEFAULT;
	this->alto_px = (alto_px_in > 0) ? alto_px_in : ALTOPX_VENTANA_DEFAULT;
	this->ancho = (ancho_in > 0) ? ancho_in : ANCHO_VENTANA_DEFAULT;
}

void VentanaDef::ajustarAncho(double anchoEscenario){
    if (ancho > anchoEscenario) {
        ancho = anchoEscenario / 2;
        Logger::getInstance()->info("El ancho de la ventana es mas grande que el ancho del escenario. Se elije uno nuevo que es la mitad del ancho del escenario");
    }
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

ostream& operator <<(ostream &o, const VentanaDef &v) {

        o<<"VentanaDef -> [anchopx, altopx, ancho]=["<<v.ancho_px<<", "<<v.alto_px<<", "<<v.ancho<<"]";

        return o;
}

string VentanaDef::toString() {
    ostringstream stream;
    stream <<*this;
	return stream.str();
}
