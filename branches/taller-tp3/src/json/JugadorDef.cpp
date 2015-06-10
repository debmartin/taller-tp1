/*
 * JugadorDef.cpp
 *
 *  Created on: 1/5/2015
 *      Author: ariel
 */

#include "JugadorDef.h"

#include <sstream>

#include "ControlDef.h"

JugadorDef::JugadorDef() {
	// TODO Auto-generated constructor stub

}

JugadorDef::JugadorDef(string tipo_control, int tolerancia, ControlDef* controlDef) {
	this->idPersonaje = "";
	this->tipo_control = tipo_control;
	this->tolerancia = tolerancia;
	this->controlDef = controlDef;
}

string JugadorDef::toString() {
    ostringstream stream;
    stream <<*this;
	return stream.str();
}

string JugadorDef::getTipoControl() const {
	return tipo_control;
}

int JugadorDef::getTolerancia() const {
	return tolerancia;
}

ControlDef* JugadorDef::getControlDef() const {
	return controlDef;
}

string JugadorDef::getIdPersonaje() const {
	return idPersonaje;
}

JugadorDef::~JugadorDef() {
	// TODO Auto-generated destructor stub
}

ostream& operator <<(ostream &o, const JugadorDef &j) {

	o<<"JugadorDef -> [personaje, tipo_control]=["<<j.idPersonaje<<","<<j.idPersonaje<<"]";
	o<<"JugadorDef -> [control]=["<<*j.controlDef<<"]";
	return o;
}

void JugadorDef::cargarIdPersonajeDesdeMenu(string nuevoIdPersonaje) {
	this->idPersonaje = nuevoIdPersonaje;
}
