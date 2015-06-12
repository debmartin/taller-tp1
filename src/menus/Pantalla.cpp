/*
 * Pantalla.cpp
 *
 *  Created on: 30/5/2015
 *      Author: ariel
 */

#include "Pantalla.h"

Pantalla::Pantalla(int anchopx, int altopx, string tipoDeControl_jugador1,
		string tipoDeControl_jugador2) {
	this->tipoDeControl_jugador1 = tipoDeControl_jugador1;
	this->tipoDeControl_jugador2 = tipoDeControl_jugador2;
	this->anchopx = anchopx;
	this->altopx = altopx;
}

Pantalla::~Pantalla() {
	// TODO Auto-generated destructor stub
}

string Pantalla::getTipoDeControlJugador1() const {
	return tipoDeControl_jugador1;
}

string Pantalla::getTipoDeControlJugador2() const {
	return tipoDeControl_jugador2;
}

int Pantalla::getAnchopx() const {
	return anchopx;
}

int Pantalla::getAltopx() const {
	return altopx;
}
