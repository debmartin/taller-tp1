/*
 * ControlJoystickDef.h
 *
 *  Created on: 9/5/2015
 *      Author: ariel
 */

#ifndef SRC_JSON_CONTROLJOYSTICKDEF_H_
#define SRC_JSON_CONTROLJOYSTICKDEF_H_

#include <iostream>
#include <string>

#include "../utils/Loggeable.h"

using namespace std;

class ControlJoystickDef: public Loggeable {
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
	ControlJoystickDef();
	ControlJoystickDef(string id, string izq, string der, string arri, string abajo, string arrojarArma, string golpeAlto, string patadaAlta, string bloquear);
	virtual ~ControlJoystickDef();
	friend ostream& operator<<(ostream &o, const ControlJoystickDef &c);
	string toString();
};

#endif /* SRC_JSON_CONTROLJOYSTICKDEF_H_ */
