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

#include "../modelo/Vector2f.h"
#include "SpriteDef.h"
#include "ColorAlternativoDef.h"


#define ALTO_PERS_DEFAULT 150
#define ANCHO_PERS_DEFAULT 50
#define Z_INDEX_PERS_DEFAULT 3
#define DIRECCION_PERS_DERECHA 1
#define DIRECCION_PERS_IZQUIERDA -1
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
	int direccion;
	Vector2f posicionInicial;
	ColorAlternativoDef* colorAlternativoDef;

public:
	PersonajeDef();
	PersonajeDef(double ancho, double alto, int zindex, int direccion, Vector2f posInicial, ColorAlternativoDef* colorAlter);
	virtual ~PersonajeDef();
	double getAlto() const;
	double getAncho() const;
	int getZindex() const;
	void setAlto(double nuevoAlto);
	void setAncho(double nuevoAncho);
	void setZIndex(int z);
	Vector2f getPosicionInicial();
	ColorAlternativoDef* getColorAlternativoDef() const;
	void setColorAlternativoDef(ColorAlternativoDef* colorAlternativoDef);

	list<SpriteDef*>* getSpritesDef() const;
	void agregarSpritesDef(SpriteDef* spriteDef);

	int getDireccion() const;
	void setDireccion(int nuevaDir);
    void ajustarZIndex(int cantCapas);
    void ajustarAlto(double altoEscenario, double ypiso);
    void ajustarPosicionIncial(double anchoEscenario, double anchoVentana, double ypiso);
    void ajustarColorAlternativo();
	friend ostream& operator<<(ostream &o, const PersonajeDef &p);

	string toString();

};

#endif /* SRC_JSON_PERSONAJEDEF_H_ */
