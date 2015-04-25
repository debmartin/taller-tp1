/*
 * SpriteDef.cpp
 *
 *  Created on: 14/4/2015
 *      Author: ariel
 */

#include "SpriteDef.h"

#include <sstream>

#include "../utils/Logger.h"
#include "../utils/Util.h"


SpriteDef::SpriteDef() {
	this->imagen = "no_imagen";
	this->id_sprite = "no_id";
	this->cant_fotogramas = 0;
	this->fps = 0;
}

SpriteDef::SpriteDef(string imagen_in, string id, int cant_fotogramas_in, int fps_in) {
    this->id_sprite = id;

    if ( !Util::getInstancia()->existeArchivo(imagen_in) ) {
        Logger::getInstance()->info("No existen las imagenes del sprites "+imagen_in+". Por defecto se usa sprites_defecto.png");
        imagen = IMAGEN_DEFAULT;
        cant_fotogramas = 9;
        fps = 10;
        return;
    }
    if ( cant_fotogramas_in <= 0 )
        Logger::getInstance()->info("la cant. de fotogramas de la imagen del sprite del personaje es menor o igual a cerop. Se elije uno nuevo con el valor de 1");
    if ( fps_in <= 0 )
        Logger::getInstance()->info("el valor de los fps del sprite del personaje es menor o igual a cerop. Se elije uno nuevo con el valor de 10");

    this->imagen = imagen_in;
	this->cant_fotogramas = (cant_fotogramas_in > 0) ? cant_fotogramas_in : CANT_FOTOGRAMAS_DEFAULT;
	this->fps = (fps_in > 0) ? fps_in : FPS_DEFAULT;
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
