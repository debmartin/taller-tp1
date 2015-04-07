/*
 * Escenario.h
 *
 *  Created on: 19/3/2015
 *      Author: ariel
 */

#ifndef SRC_MODELO_ESCENARIO_H_
#define SRC_MODELO_ESCENARIO_H_

#include <iostream>
using namespace std;

class Escenario {
private:
	double ancho;
	double alto;
	double ypiso;

public:
	Escenario();
	Escenario(double ancho, double alto, double ypiso);
	virtual ~Escenario();
	double getAlto() const;
	double getAncho() const;
	double getYpiso() const;

	friend ostream& operator<<(ostream &o, const Escenario &e);
};

#endif /* SRC_MODELO_ESCENARIO_H_ */
