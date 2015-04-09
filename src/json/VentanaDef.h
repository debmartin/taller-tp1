/*
 * VentanaDef.h
 *
 *  Created on: 9/4/2015
 *      Author: ariel-vm-barza
 */

#ifndef SRC_JSON_VENTANADEF_H_
#define SRC_JSON_VENTANADEF_H_

#include <iostream>
using namespace std;

class VentanaDef {
private:
	int ancho_px;
	int alto_px;
	double ancho;
	double margen_x;
public:
	VentanaDef();
	VentanaDef(int ancho_px, int alto_px, double ancho, double margen_x);
	virtual ~VentanaDef();
	int getAltoPx() const;
	double getAncho() const;
	int getAnchoPx() const;
	double getMargenX() const;

	friend ostream& operator<<(ostream &o, const VentanaDef &v);
};

#endif /* SRC_JSON_VENTANADEF_H_ */
