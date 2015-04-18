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

class PersonajeDef: public ObjetoJson {
private:
	double ancho;
	double alto;
	int z_index;
	list<SpriteDef*>* spritesDef;
	int direccion;
	string id;

public:
	PersonajeDef();
	PersonajeDef(double ancho, double alto, int zindex, int direccion, string id);
	virtual ~PersonajeDef();
	double getAlto() const;
	double getAncho() const;
	int getZindex() const;
	void setAlto(double nuevoAlto);
	void setAncho(double nuevoAncho);
	void setZIndex(int z);
	string getId() const;

	list<SpriteDef*>* getSpritesDef() const;
	void agregarSpritesDef(SpriteDef* spriteDef);

	int getDireccion() const;
	void setDireccion(int nuevaDir);

	friend ostream& operator<<(ostream &o, const PersonajeDef &p);

	string toString();
};

#endif /* SRC_JSON_PERSONAJEDEF_H_ */
