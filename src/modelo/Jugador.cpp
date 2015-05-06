/*
 * Jugador.cpp
 *
 *  Created on: 5/5/2015
 *      Author: ariel
 */

#include "Jugador.h"

#include "Personaje.h"

Jugador::Jugador() {
}

Jugador::Jugador(Personaje* personaje, PersonajeDibujable* personajeDibujable) {
	this->personaje = personaje;
	this->personajeDibujable = personajeDibujable;
}

Personaje* Jugador::getPersonaje() const {
	return personaje;
}

void Jugador::setPersonaje(Personaje* personaje) {
	this->personaje = personaje;
}

PersonajeDibujable* Jugador::getPersonajeDibujable() const {
	return personajeDibujable;
}

void Jugador::setPersonajeDibujable(PersonajeDibujable* personajeDibujable) {
	this->personajeDibujable = personajeDibujable;
}

Jugador::~Jugador() {
	// TODO Auto-generated destructor stub
}

void Jugador::posicionarPersonaje_enEjeX(double x) {
	this->personaje->definirPosicionIncial_enX(x);
}
