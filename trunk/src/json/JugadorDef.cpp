/*
 * JugadorDef.cpp
 *
 *  Created on: 1/5/2015
 *      Author: ariel
 */

#include "JugadorDef.h"

#include <sstream>

JugadorDef::JugadorDef() {
	// TODO Auto-generated constructor stub

}

JugadorDef::JugadorDef(string personaje, ControlJoystickDef* controlJoystick) {
	this->idPersonaje = personaje;
	this->controlJoystick = controlJoystick;
}

string JugadorDef::toString() {
    ostringstream stream;
    stream <<*this;
	return stream.str();
}

ControlJoystickDef* JugadorDef::getControlJoystick() const {
	return controlJoystick;
}

string JugadorDef::getIdPersonaje() const {
	return idPersonaje;
}

JugadorDef::~JugadorDef() {
	// TODO Auto-generated destructor stub
}

ostream& operator <<(ostream &o, const JugadorDef &j) {

	o<<"JugadorDef -> [personaje]=["<<j.idPersonaje<<"]";
	return o;
}
