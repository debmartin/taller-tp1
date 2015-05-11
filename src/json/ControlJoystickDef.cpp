/*
 * ControlJoystickDef.cpp
 *
 *  Created on: 9/5/2015
 *      Author: ariel
 */

#include "ControlJoystickDef.h"

#include <sstream>


ControlJoystickDef::ControlJoystickDef() {
	// TODO Auto-generated constructor stub

}

ControlJoystickDef::ControlJoystickDef(string id, string izq, string der, string arriba, string abajo, string arrojarArma,
													string golpeAlto, string patadaAlta, string bloquear) {
	this->id = id;
	this->izq = izq;
	this->der = der;
	this->arriba = arriba;
	this->abajo = abajo;
	this->arrojarArma = arrojarArma;
	this->golpeAlto = golpeAlto;
	this->patadaAlta = patadaAlta;
	this->bloquear = bloquear;
}

ControlJoystickDef::~ControlJoystickDef() {
	// TODO Auto-generated destructor stub
}

ostream& operator <<(ostream &o, const ControlJoystickDef &c) {

        o<<"ControlJoystickDef -> [id, izq, der, arriba, abajo, arrojarArma, golpeAlto, patadaAlta, bloquear]=[";
        o<<c.id<<", "<<c.izq<<", "<<c.der<<", "<<c.arriba<<", "<<c.abajo<<", ";
        o<<c.arrojarArma<<", "<<c.golpeAlto<<", "<<c.patadaAlta<<", "<<c.bloquear<<"]";
        return o;
}

string ControlJoystickDef::toString() {
    ostringstream stream;
    stream <<*this;
	return stream.str();
}

