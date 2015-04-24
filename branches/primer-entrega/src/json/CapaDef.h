/*
 * CapaDef.h
 *
 *  Created on: 9/4/2015
 *      Author: ariel-vm-barza
 */

#ifndef SRC_JSON_CAPADEF_H_
#define SRC_JSON_CAPADEF_H_

#include <iostream>
#include <string>

#include "ObjetoJson.h"
#include "../utils/Util.h"
#include "../utils/Logger.h"

#define IMAGEN_CAPA_DEFAULT "img/fondo_capa_defecto.png"
#define ANCHO_CAPA_DEFAULT 1200

using namespace std;

class CapaDef: public ObjetoJson {
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
    void ajustarAncho(double anchoEscenario, double anchoVentana);
	friend ostream& operator<<(ostream &o, const CapaDef &c);
	string toString();
};

#endif /* SRC_JSON_CAPADEF_H_ */
