/*
 * CapaDef.h
 *
 *  Created on: 9/4/2015
 *      Author: ariel-vm-barza
 */

#ifndef SRC_JSON_CAPADEF_H_
#define SRC_JSON_CAPADEF_H_
#include <iostream>
#include <string.h>
using namespace std;

class CapaDef {
private:
	string imagen_fondo;
	string id_capa;
	double ancho;
public:
	CapaDef();
	CapaDef(string imagen_fondo, string id, double ancho);
	virtual ~CapaDef();
	double getAncho() const;
	string getImagenFondo() const;
	string getIdCapa() const;

	friend ostream& operator<<(ostream &o, const CapaDef &c);
};

#endif /* SRC_JSON_CAPADEF_H_ */
