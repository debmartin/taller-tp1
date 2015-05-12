/*
 * ControlDef.h
 *
 *  Created on: 11/5/2015
 *      Author: ariel
 */

#ifndef SRC_JSON_CONTROLDEF_H_
#define SRC_JSON_CONTROLDEF_H_

#include <iostream>
#include <string>

#include "../utils/Loggeable.h"

using namespace std;

class ControlDef: public Loggeable {
private:
        string id;
        string izq;
        string der;
        string arriba;
        string abajo;
        string arrojarArma;
        string golpeAlto;
        string patadaAlta;
        string bloquear;

public:
	ControlDef();
	ControlDef(string id, string izq, string der, string arri, string abajo, string arrojarArma, string golpeAlto, string patadaAlta, string bloquear);
	virtual ~ControlDef();
    friend ostream& operator<<(ostream &o, const ControlDef &c);
    string toString();

};

#endif /* SRC_JSON_CONTROLDEF_H_ */
