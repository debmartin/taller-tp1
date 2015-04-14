/*
 * SpriteDef.cpp
 *
 *  Created on: 14/4/2015
 *      Author: ariel
 */

#include "SpriteDef.h"

SpriteDef::SpriteDef() {

}

SpriteDef::SpriteDef(string imagen, double ancho, int cant_fotogramas,
		int fps) {

	this->imagen = imagen;
	this->ancho = ancho;
	this->cant_fotogramas = cant_fotogramas;
	this->fps = fps;
}

double SpriteDef::getAncho() const {
	return ancho;
}

int SpriteDef::getCantFotogramas() const {
	return cant_fotogramas;
}

int SpriteDef::getFps() const {
	return fps;
}

const string& SpriteDef::getImagen() const {
	return imagen;
}

SpriteDef::~SpriteDef() {
	// TODO Auto-generated destructor stub
}

ostream& operator <<(ostream &o, const SpriteDef &p) {

        o<<"SpriteDef -> [imagen, ancho, cant_fotogramas, fps]=[";
        o<<p.imagen<<", "<<p.ancho<<", "<<p.cant_fotogramas<<", "<<p.fps<<"]";

        return o;
}
