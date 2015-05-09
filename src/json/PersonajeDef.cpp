/*
 * PersonajeDef.cpp
 *
 *  Created on: 9/4/2015
 *      Author: ariel-vm-barza
 */

#include "PersonajeDef.h"

#include <sstream>

#include "../utils/Logger.h"
#include "ColorAlternativoDef.h"

#define ANCHO_ESCENARIO 600

PersonajeDef::PersonajeDef() {
	this->ancho = 0;
	this->alto = 0;
	this->z_index = 0;
	this->spritesDef = new list<SpriteDef*>();
	this->id = "";
	this->colorAlternativoDef = new ColorAlternativoDef();
	cajasColisiones = NULL;
}

PersonajeDef::PersonajeDef(string id, double anchoIn, double altoIn, int zindexIn, ColorAlternativoDef* colorAlter)
{
	this->id = id;

    if (anchoIn <= 0)
		Logger::getInstance()->info("El ancho del personaje es menor o igual a cero. Se elije uno nuevo con el valor de 15");
    if (altoIn <= 0)
		Logger::getInstance()->info("El alto del personaje es menor o igual a cero. Se elije uno nuevo con el valor de 60");
    if ( zindexIn < 0 )
        Logger::getInstance()->info("El zindex del personaje es menor a cero. Se elije uno nuevo para que el personaje este adelante de todas las capas");

    /* TODO pasar a jugador ...
   	if (direccionIn != DIRECCION_PERS_DERECHA && direccionIn != DIRECCION_PERS_IZQUIERDA)	{
		direccionIn = DIRECCION_PERS_DERECHA;
		Logger::getInstance()->info("La configuracion de la direccion del personaje no es la correcta. Se lo dirije en direccion derecha");
	}
	*/

	this->ancho = (anchoIn > 0) ? anchoIn : ANCHO_PERS_DEFAULT;
	this->alto = (altoIn > 0) ? altoIn : ALTO_PERS_DEFAULT;
	this->z_index = (zindexIn >= 0) ? zindexIn : Z_INDEX_PERS_DEFAULT;
	this->spritesDef = new list<SpriteDef*>();
	this->colorAlternativoDef = colorAlter;
	cajasColisiones = NULL;
}

void PersonajeDef::ajustarZIndex(int cantCapas)
{
    if (z_index > cantCapas)
    {
        z_index = cantCapas;
        Logger::getInstance()->error("El zindex del Personaje es mayor al valor posible. Se elije uno nuevo para que el personaje este adelante de todas las capas. Valor", z_index);
    }
}

void PersonajeDef::ajustarAlto(double altoEscenario, double ypiso){
    if (alto <= 0) {
    	alto = altoEscenario / 3;
		Logger::getInstance()->info("El alto del personaje es negativo. Se elije uno nuevo",alto);
	}

    if ( alto >  ( altoEscenario - ypiso ) )
    {
    	alto = altoEscenario / 3;
    	Logger::getInstance()->info("El alto del personaje sobrepasa la altura del escenario. Se elije uno nuevo",alto);
    }
}

void PersonajeDef::ajustarColorAlternativo() {
	// TODO falta validacion
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

void PersonajeDef::setAlto(double nuevoAlto) {
	alto = nuevoAlto;
}

void PersonajeDef::setAncho(double nuevoAncho){
	ancho = nuevoAncho;
}

void PersonajeDef::setZIndex(int nuevoZIndex) {
	z_index = nuevoZIndex;
}

PersonajeDef::~PersonajeDef(){
	for (list<SpriteDef*>::iterator it_spritesDef = spritesDef->begin() ; it_spritesDef !=  spritesDef->end(); it_spritesDef++){
            delete *it_spritesDef;
	}
	delete spritesDef;
}

list<SpriteDef*>* PersonajeDef::getSpritesDef() const {
	return spritesDef;
}

ostream& operator <<(ostream &o, const PersonajeDef &p) {

        o<<"PersonajeDef -> [id, ancho, alto, zindex]=[";
        o<<p.id<<", "<<p.ancho<<", "<<p.alto<<", "<<p.z_index<<"]"<<endl;
        o<<"sprites: {"<<endl;
    	for (list<SpriteDef*>::iterator it_spritesDef = p.getSpritesDef()->begin() ; it_spritesDef !=  p.getSpritesDef()->end(); it_spritesDef++)
    	{
    		o<<**it_spritesDef<<endl;
    	}
    	o<<"}";
    	o<<*p.getColorAlternativoDef();
        return o;
}

void PersonajeDef::agregarSpritesDef(SpriteDef* spriteDef) {
	this->spritesDef->push_back(spriteDef);
}

void PersonajeDef::agregarArmaDef(ArmaDef* arma){
	this->armaArrojable = arma;
}

ArmaDef* PersonajeDef::getArmaDef(){
	return armaArrojable;
}

string PersonajeDef::toString() {
    ostringstream stream;
    stream <<*this;
	return stream.str();
}

ColorAlternativoDef* PersonajeDef::getColorAlternativoDef() const {
	return colorAlternativoDef;
}

void PersonajeDef::setColorAlternativoDef(ColorAlternativoDef* colorAlternativoDef) {
	this->colorAlternativoDef = colorAlternativoDef;
}

string PersonajeDef::getId() const {
	return id;
}

void PersonajeDef::setId(string id) {
	this->id = id;
}

map<estado_personaje, BVH*>* PersonajeDef::getCajasCol(){
    return cajasColisiones;
}
