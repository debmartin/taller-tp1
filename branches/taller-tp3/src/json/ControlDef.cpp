/*
 * ControlDef.cpp
 *
 *  Created on: 11/5/2015
 *      Author: ariel
 */

#include "ControlDef.h"

#include <sstream>
#include <utility>

ControlDef::ControlDef() {
	// TODO Auto-generated constructor stub

}

ControlDef::ControlDef(map<string, int>* correspondenciaTeclas, map<string, int>* correspondenciaEjes) {
	this->correspondenciaTeclas = correspondenciaTeclas;
	this->correspondenciaEjes = correspondenciaEjes;
}

ostream& operator <<(ostream &o, const ControlDef &c) {

        o<<"ControlDef -> [NOMBRE CONTROL, valor del control]:";
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

string ControlDef::toString() {
    ostringstream stream;
    stream <<*this;
    return stream.str();
}


ControlDef::~ControlDef() {
	// TODO Auto-generated destructor stub
}

std::map<string, int>* ControlDef::getCorrespondenciaEjes() const {
	return correspondenciaEjes;
}

std::map<string, int>* ControlDef::getCorrespondenciaTeclas() const {
	return correspondenciaTeclas;
}

