/*
 * PersonajeDef.h
 *
 *  Created on: 9/4/2015
 *      Author: ariel-vm-barza
 */

#ifndef SRC_JSON_PERSONAJEDEF_H_
#define SRC_JSON_PERSONAJEDEF_H_

#include <iostream>
#include <list>
#include <string>

#include "SpriteDef.h"

class SpriteDef;

using namespace std;

class PersonajeDef {
private:
	double ancho;
	double alto;
	int z_index;
	list<SpriteDef*>* spritesDef;
	int direccion;

public:
	PersonajeDef();
	PersonajeDef(double ancho, double alto, int zindex, int direccion);
	virtual ~PersonajeDef();
	double getAlto() const;
	double getAncho() const;
	int getZindex() const;
	void setAlto(double nuevoAlto);
	void setAncho(double nuevoAncho);
	void setZIndex(int z);

	list<SpriteDef*>* getSpritesDef() const;
	void agregarSpritesDef(SpriteDef* spriteDef);

	int getDireccion() const;
	void setDireccion(int nuevaDir);

	friend ostream& operator<<(ostream &o, const PersonajeDef &p);
};

#endif /* SRC_JSON_PERSONAJEDEF_H_ */
