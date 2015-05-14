/*
 * Control.h
 *
 *  Created on: 11/5/2015
 *      Author: ariel
 */

#ifndef SRC_CONTROLADOR_CONTROL_H_
#define SRC_CONTROLADOR_CONTROL_H_

#include <iostream>
#include <map>
#include <string>

#include "../utils/Loggeable.h"

class ControlDef;

using namespace std;

class Control: public Loggeable {
protected:
	map<string, int>* correspondenciaTeclas;
	map<string, int>* correspondenciaEjes;
public:
	Control();
	Control(ControlDef* controlDef);
	virtual ~Control();
	map<string, int>* getCorrespondenciaEjes() const;
	map<string, int>* getCorrespondenciaTeclas() const;
	string toString();
	friend ostream& operator<<(ostream &o, const Control &c);
};

#endif /* SRC_CONTROLADOR_CONTROL_H_ */
