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

JugadorDef::JugadorDef(string personaje, int direccion) {
	this->idPersonaje = personaje;
	this->direccion = direccion;
}

string JugadorDef::toString() {
    ostringstream stream;
    stream <<*this;
	return stream.str();
}

int JugadorDef::getDireccion() const {
	return direccion;
}

void JugadorDef::setDireccion(int direccion) {
	this->direccion = direccion;
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
