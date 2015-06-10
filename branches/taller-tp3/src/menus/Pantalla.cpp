/*
 * Pantalla.cpp
 *
 *  Created on: 30/5/2015
 *      Author: ariel
 */

#include "Pantalla.h"

Pantalla::Pantalla() {

}

Pantalla::Pantalla(string tipoDeControl_jugador1,
		string tipoDeControl_jugador2) {
	this->tipoDeControl_jugador1 = tipoDeControl_jugador1;
	this->tipoDeControl_jugador2 = tipoDeControl_jugador2;
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
