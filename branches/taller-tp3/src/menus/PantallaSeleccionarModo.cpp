/*
 * PantallaSeleccionarModo.cpp
 *
 *  Created on: 30/5/2015
 *      Author: ariel
 */

#include "PantallaSeleccionarModo.h"

PantallaSeleccionarModo::PantallaSeleccionarModo() {
	this->modo_juego_elegido = JUEGO_MODO_P1_VS_P2;

}

PantallaSeleccionarModo::~PantallaSeleccionarModo() {

}

void PantallaSeleccionarModo::iniciar() {

	//TODO elegir desde del menu ...

	this->modo_juego_elegido = JUEGO_MODO_P1_VS_P2;

}

string PantallaSeleccionarModo::getModoDeJuegoElegido() {
	return this->modo_juego_elegido;
}
