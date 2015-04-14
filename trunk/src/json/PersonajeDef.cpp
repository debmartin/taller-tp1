/*
 * PersonajeDef.cpp
 *
 *  Created on: 9/4/2015
 *      Author: ariel-vm-barza
 */

#include "PersonajeDef.h"

#define ANCHO_ESCENARIO 600

PersonajeDef::PersonajeDef() {
	this->ancho = 0;
	this->alto = 0;
}

PersonajeDef::PersonajeDef(double ancho, double alto, int zindex,
		string sprites_imagen, double sprites_ancho, int sprites_cant_fotogramas,
		int sprites_fps, int direccion)
{
	this->ancho = ancho;
	this->alto = alto;
	this->z_index = zindex;
	this->sprites_imagen = sprites_imagen;
	this->sprites_ancho = sprites_ancho;
	this->sprites_cant_fotogramas = sprites_cant_fotogramas;
	this->sprites_fps = sprites_fps;
	this->direccion = direccion;
}

double PersonajeDef::getAlto() const {
	return alto;
}

double PersonajeDef::getAncho() const {
	return ancho;
}

int PersonajeDef::getZindex() const {
	return z_index;
}

double PersonajeDef::getSpritesAncho() const {
	return sprites_ancho;
}

const string& PersonajeDef::getSpritesImagen() const {
	return sprites_imagen;
}

PersonajeDef::~PersonajeDef(){
	// TODO Auto-generated destructor stub
}

int PersonajeDef::getSpritesCantFotogramas() const {
	return sprites_cant_fotogramas;
}

int PersonajeDef::getSpritesFps() const {
	return sprites_fps;
}

ostream& operator <<(ostream &o, const PersonajeDef &p) {

        o<<"PersonajeDef -> [ancho, alto, zindex, sprites_imagen, sprites_ancho, sprites_cant_fotogramas, sprites_fps, direccion]=[";
        o<<p.ancho<<", "<<p.alto<<", "<<p.z_index<<", "<<p.sprites_imagen<<", "<<p.sprites_ancho<<", ";
        o<<p.sprites_cant_fotogramas<<", "<<p.sprites_fps<<", "<<p.direccion<<"]";

        return o;
}

int PersonajeDef::getDireccion() const {
	return direccion;
}

