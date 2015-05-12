/*
 * ControlDef.cpp
 *
 *  Created on: 11/5/2015
 *      Author: ariel
 */

#include "ControlDef.h"

#include <sstream>

ControlDef::ControlDef() {
	// TODO Auto-generated constructor stub

}

ControlDef::ControlDef(string id, string izq, string der, string arriba, string abajo, string arrojarArma,
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

ostream& operator <<(ostream &o, const ControlDef &c) {

        o<<"ControlDef -> [id, izq, der, arriba, abajo, arrojarArma, golpeAlto, patadaAlta, bloquear]=[";
        o<<c.id<<", "<<c.izq<<", "<<c.der<<", "<<c.arriba<<", "<<c.abajo<<", ";
        o<<c.arrojarArma<<", "<<c.golpeAlto<<", "<<c.patadaAlta<<", "<<c.bloquear<<"]";
        return o;
}

string ControlDef::toString() {
    ostringstream stream;
    stream <<*this;
    return stream.str();
}


ControlDef::~ControlDef() {
	// TODO Auto-generated destructor stub
}

