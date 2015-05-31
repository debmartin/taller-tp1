/*
 * PantallaSeleccionarPersonaje.cpp
 *
 *  Created on: 30/5/2015
 *      Author: ariel
 */

#include "PantallaSeleccionarPersonaje.h"

PantallaSeleccionarPersonaje::PantallaSeleccionarPersonaje(string modo_juego_elegido) {
	this->modo_juego_elegido = modo_juego_elegido;
}

PantallaSeleccionarPersonaje::~PantallaSeleccionarPersonaje() {
	// TODO Auto-generated destructor stub
}

void PantallaSeleccionarPersonaje::iniciar() {

	//TODO elegir desde del menu ...

	this->IdPersonaje1Elegido = "sub-zero";
	this->IdPersonaje2Elegido = "sonya";

}

string PantallaSeleccionarPersonaje::getIdPersonaje1Elegido() {
	return this->IdPersonaje1Elegido;
}

string PantallaSeleccionarPersonaje::getIdPersonaje2Elegido() {
	return this->IdPersonaje2Elegido;
}
