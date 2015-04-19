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
#include "../utils/Logger.h"

#define ALTO_ESC_DEFAULT 180
#define ANCHO_ESC_DEFAULT 1200
#define Y_PISO_ESC_DEFAULT 0

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

    void ajustarYPiso(double altoPersonaje);
	friend ostream& operator<<(ostream &o, const EscenarioDef &e);
	string toString();
};

#endif /* SRC_JSON_ESCENARIODEF_H_ */
