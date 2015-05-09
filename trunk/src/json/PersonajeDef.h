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
#include <map>

#include "SpriteDef.h"

#include "ArmaDef.h"
#include "../modelo/estado/Estado.h"
#include "../modelo/fisica/BVH.h"

class ColorAlternativoDef;


#define ALTO_PERS_DEFAULT 150
#define ANCHO_PERS_DEFAULT 50
#define Z_INDEX_PERS_DEFAULT 3
#define COLOR_ALTERNATIVO_HINICIAL_PERS_DEFAULT 40
#define COLOR_ALTERNATIVO_HFINAL_PERS_DEFAULT 45
#define COLOR_ALTERNATIVO_DESPLAZAMIENTO_PERS_DEFAULT 30

class SpriteDef;

using namespace std;

class PersonajeDef: public Loggeable {
private:
	double ancho;
	double alto;
	int z_index;
	list<SpriteDef*>* spritesDef;
	ArmaDef* armaArrojable;
	float velocidadArma;
	ColorAlternativoDef* colorAlternativoDef;
	string id;
	map<estado_personaje, BVH*>* cajasColisiones;

public:
	PersonajeDef();
	PersonajeDef(string id, double ancho, double alto, int zindex, ColorAlternativoDef* colorAlter);
	virtual ~PersonajeDef();
	double getAlto() const;
	double getAncho() const;
	int getZindex() const;
	void setAlto(double nuevoAlto);
	void setAncho(double nuevoAncho);
	void setZIndex(int z);
	ColorAlternativoDef* getColorAlternativoDef() const;
	void setColorAlternativoDef(ColorAlternativoDef* colorAlternativoDef);

	list<SpriteDef*>* getSpritesDef() const;
	void agregarSpritesDef(SpriteDef* spriteDef);
	void agregarArmaDef(ArmaDef* arma);
	ArmaDef* getArmaDef();
    void ajustarZIndex(int cantCapas);
    void ajustarAlto(double altoEscenario, double ypiso);
    void ajustarColorAlternativo();
	friend ostream& operator<<(ostream &o, const PersonajeDef &p);

    std::map<estado_personaje, BVH*>* getCajasCol();

	string toString();
	string getId() const;
	void setId(string id);
};

#endif /* SRC_JSON_PERSONAJEDEF_H_ */
