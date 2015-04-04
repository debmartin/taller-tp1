/*
 * Capa.h
 *
 *  Created on: 19/3/2015
 *      Author: ariel
 */

#ifndef SRC_MODELO_CAPA_H_
#define SRC_MODELO_CAPA_H_

#include <iostream>
#include <string.h>
using namespace std;

class Capa {
private:
	string imagen_fondo;
	double ancho;
public:
	Capa();
	Capa(string imagen_fondo, double ancho);
	virtual ~Capa();
	double getAncho() const;
	string getImagenFondo() const;

	friend ostream& operator<<(ostream &o, const Capa &c);
};

#endif /* SRC_MODELO_CAPA_H_ */
