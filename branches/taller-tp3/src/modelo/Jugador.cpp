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

Jugador::Jugador(Personaje* personaje, PersonajeDibujable* personajeDibujable, Control* control, string tipo_control, MapaDeCombos* mapa) {
	this->personaje = personaje;
	this->personajeDibujable = personajeDibujable;
	this->control = control;
	this->mapa_de_combos = mapa;
	this->tipo_control = tipo_control;
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

Control* Jugador::getControl() const {
	return control;
}

string Jugador::getTipoControl() const {
	return tipo_control;
}

MapaDeCombos* Jugador::getMapaDeCombos() {
	return mapa_de_combos;
}
