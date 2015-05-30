/*
 * Control.cpp
 *
 *  Created on: 11/5/2015
 *      Author: ariel
 */

#include "Control.h"

#include <sstream>
#include <utility>

#include "../json/ControlDef.h"

Control::Control() {

}

Control::Control(ControlDef* controlDef) {
	this->correspondenciaTeclas = controlDef->getCorrespondenciaTeclas();
	this->correspondenciaEjes = controlDef->getCorrespondenciaEjes();
}

map<string, int>*Control::getCorrespondenciaEjes() const {
	return correspondenciaEjes;
}

map<string, int>* Control::getCorrespondenciaTeclas() const {
	return correspondenciaTeclas;
}

Control::~Control() {
	// TODO Auto-generated destructor stub
}

string Control::toString() {
    ostringstream stream;
    stream <<*this;
    return stream.str();
}

ostream& operator <<(ostream &o, const Control &c) {

        o<<"Control -> [NOMBRE CONTROL, valor del control]:";
        for (map<string, int>::iterator it = c.correspondenciaTeclas->begin() ; it != c.correspondenciaTeclas->end(); ++it)
        {
        	o<<"["<<it->first<<"]="<<it->second<<endl;
        }
        for (map<string, int>::iterator it = c.correspondenciaEjes->begin() ; it != c.correspondenciaEjes->end(); ++it)
        {
        	o<<"["<<it->first<<"]="<<it->second<<endl;
        }
        return o;
}

