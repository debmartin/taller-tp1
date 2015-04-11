/*
 * PersonajeDef.h
 *
 *  Created on: 9/4/2015
 *      Author: ariel-vm-barza
 */

#ifndef SRC_JSON_PERSONAJEDEF_H_
#define SRC_JSON_PERSONAJEDEF_H_

#include <iostream>
#include <string>

using namespace std;

class PersonajeDef {
private:
	double ancho;
	double alto;
	int z_index;
	string sprites_imagen;
	double sprites_ancho;
	int direccion;

public:
	PersonajeDef();
	PersonajeDef(double ancho, double alto, int zindex, string sprites_imagen, double sprites_ancho, int direccion);
	virtual ~PersonajeDef();
	double getAlto() const;
	double getAncho() const;
	int getZindex() const;
	double getSpritesAncho() const;
	const string& getSpritesImagen() const;
	int getDireccion() const;

	friend ostream& operator<<(ostream &o, const PersonajeDef &p);
};

#endif /* SRC_JSON_PERSONAJEDEF_H_ */
