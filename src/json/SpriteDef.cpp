/*
 * SpriteDef.cpp
 *
 *  Created on: 14/4/2015
 *      Author: ariel
 */

#include "SpriteDef.h"
#include "../utils/Util.h"

SpriteDef::SpriteDef() {

}

SpriteDef::SpriteDef(string imagen, string id, double ancho, int cant_fotogramas,
		int fps) {

	this->imagen = imagen;
	this->id_sprite = id;
	this->ancho = ancho;
	this->cant_fotogramas = cant_fotogramas;
	this->fps = fps;
//	if ( !Util::getInstancia()->existeArchivo(imagen) ){
//        cout << "No existe sprite arch: " << imagen << "\n";
//        throw exception();
//    } if (ancho <= 0) {
//        cout << "ancho mal\n";
//        throw exception();
//    } if (cant_fotogramas <= 0 || fps <= 0) {
//        cout << "fotogramas y fps mal\n";
//        throw exception();
//    }
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

void SpriteDef::setImagen(string nuevaImagen){
    imagen = nuevaImagen;
}

void SpriteDef::setAncho(double nuevoAncho){
	ancho = nuevoAncho;
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

        o<<"SpriteDef -> [imagen, id_sprite, ancho, cant_fotogramas, fps]=[";
        o<<p.imagen<<", "<<p.id_sprite<<", "<<p.ancho<<", "<<p.cant_fotogramas<<", "<<p.fps<<"]";

        return o;
}
