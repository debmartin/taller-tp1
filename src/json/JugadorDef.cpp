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

JugadorDef::JugadorDef(string personaje, ControlDef* controlDef) {
	this->idPersonaje = personaje;
	this->controlDef = controlDef;
}

string JugadorDef::toString() {
    ostringstream stream;
    stream <<*this;
	return stream.str();
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

	o<<"JugadorDef -> [personaje]=["<<j.idPersonaje<<"]";
	o<<"JugadorDef -> [control]=["<<*j.controlDef<<"]";
	return o;
}
