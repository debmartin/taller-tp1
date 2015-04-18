/*
 * EscenarioDef.h
 *
 *  Created on: 9/4/2015
 *      Author: ariel-vm-barza
 */

#ifndef SRC_JSON_ESCENARIODEF_H_
#define SRC_JSON_ESCENARIODEF_H_

#include <iostream>
#include <string>

#include "ObjetoJson.h"

using namespace std;

class EscenarioDef: public ObjetoJson {
private:
	double ancho;
	double alto;
	double ypiso;

public:
	EscenarioDef();
	EscenarioDef(double ancho, double alto, double ypiso);
	virtual ~EscenarioDef();
	double getAlto() const;
	double getAncho() const;
	double getYpiso() const;

	friend ostream& operator<<(ostream &o, const EscenarioDef &e);
	string toString();
};

#endif /* SRC_JSON_ESCENARIODEF_H_ */
