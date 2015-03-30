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
	int ypiso;
	//string fondo;

public:
	Escenario();
	virtual ~Escenario();
	double getAlto() const;
	void setAlto(double alto);
	double getAncho() const;
	void setAncho(double ancho);
	int getYpiso() const;
	void setYpiso(int ypiso);

	friend ostream& operator<<(ostream &o, const Escenario &e);
};

#endif /* SRC_MODELO_ESCENARIO_H_ */
