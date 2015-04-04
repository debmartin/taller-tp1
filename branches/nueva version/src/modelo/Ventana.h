/*
 * Ventana.h
 *
 *  Created on: 19/3/2015
 *      Author: ariel
 */

#ifndef SRC_MODELO_VENTANA_H_
#define SRC_MODELO_VENTANA_H_

#include <iostream>
using namespace std;

class Ventana {
private:
	int ancho_px;
	int alto_px;
	double ancho;
	double margen_x;
public:
	Ventana();
	Ventana(int ancho_px, int alto_px, double ancho, double margen_x);
	virtual ~Ventana();
	int getAltoPx() const;
	double getAncho() const;
	int getAnchoPx() const;
	double getMargenX() const;

	friend ostream& operator<<(ostream &o, const Ventana &v);
};

#endif /* SRC_MODELO_VENTANA_H_ */
