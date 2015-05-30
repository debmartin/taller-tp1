/*
 * VentanaDef.h
 *
 *  Created on: 9/4/2015
 *      Author: ariel-vm-barza
 */

#ifndef SRC_JSON_VENTANADEF_H_
#define SRC_JSON_VENTANADEF_H_

#include <iostream>
#include <string>

#include "../utils/Loggeable.h"

#define ALTOPX_VENTANA_DEFAULT 600
#define ANCHO_VENTANA_DEFAULT 600
#define ANCHOPX_VENTANA_DEFAULT 800

using namespace std;

class VentanaDef: public Loggeable {
private:
	int ancho_px;
	int alto_px;
	double ancho;
public:
	VentanaDef();
	VentanaDef(int ancho_px, int alto_px, double ancho);
	virtual ~VentanaDef();
	int getAltoPx() const;
	double getAncho() const;
	int getAnchoPx() const;
	string toString();
    void ajustarAncho(double anchoEscenario);
	friend ostream& operator<<(ostream &o, const VentanaDef &v);
};

#endif /* SRC_JSON_VENTANADEF_H_ */
