/*
 * SpriteDef.cpp
 *
 *  Created on: 14/4/2015
 *      Author: ariel
 */

#include "SpriteDef.h"

#include <sstream>


SpriteDef::SpriteDef() {
	this->imagen = "no_imagen";
	this->id_sprite = "no_id";
	this->cant_fotogramas = 0;
	this->fps = 0;
}

SpriteDef::SpriteDef(string imagen, string id, int cant_fotogramas,
		int fps) {

	this->imagen = imagen;
	this->id_sprite = id;
	this->cant_fotogramas = cant_fotogramas;
	this->fps = fps;
}

int SpriteDef::getCantFotogramas() const {
	return cant_fotogramas;
}

int SpriteDef::getFps() const {
	return fps;
}

void SpriteDef::setImagen(string nuevaImagen){
    imagen = nuevaImagen;
}

void SpriteDef::setCantFotogramas(int nuevaCant){
	cant_fotogramas = nuevaCant;
}

void SpriteDef::setFps(int nuevoFps){
    fps = nuevoFps;
}

const string& SpriteDef::getImagen() const {
	return imagen;
}

const string& SpriteDef::getIdSprite() const {
	return id_sprite;
}

SpriteDef::~SpriteDef() {
	// TODO Auto-generated destructor stub
}

ostream& operator <<(ostream &o, const SpriteDef &p) {

        o<<"SpriteDef -> [imagen, id_sprite, cant_fotogramas, fps]=[";
        o<<p.imagen<<", "<<p.id_sprite<<", "<<p.cant_fotogramas<<", "<<p.fps<<"]";

        return o;
}

string SpriteDef::toString() {
    ostringstream stream;
    stream <<*this;
	return stream.str();
}
