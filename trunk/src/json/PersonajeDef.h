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
#include "../utils/Logger.h"

#define ALTO_PERS_DEFAULT 150
#define ANCHO_PERS_DEFAULT 50
#define Z_INDEX_PERS_DEFAULT 3
#define DIRECCION_PERS_DERECHA 1
#define DIRECCION_PERS_IZQUIERDA -1

class SpriteDef;

using namespace std;

class PersonajeDef: public ObjetoJson {
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
    void ajustarZIndex();
    void ajustarAlto(double altoEscenario);
	friend ostream& operator<<(ostream &o, const PersonajeDef &p);

	string toString();
};

#endif /* SRC_JSON_PERSONAJEDEF_H_ */
