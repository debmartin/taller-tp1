/*
 * PersonajeDef.cpp
 *
 *  Created on: 9/4/2015
 *      Author: ariel-vm-barza
 */

#include "PersonajeDef.h"

#include <sstream>

#include "../utils/Logger.h"

#define ANCHO_ESCENARIO 600

PersonajeDef::PersonajeDef() {
	this->ancho = 0;
	this->alto = 0;
	this->z_index = 0;
	this->spritesDef = new list<SpriteDef*>();
	this->direccion = 1;
	this->colorAlternativoDef = new ColorAlternativoDef();
}

PersonajeDef::PersonajeDef(double anchoIn, double altoIn, int zindexIn, int direccionIn, Vector2f posInicial, ColorAlternativoDef* colorAlter)
{
    if (anchoIn <= 0)
		Logger::getInstance()->info("El ancho del personaje es menor o igual a cero. Se elije uno nuevo con el valor de 15");
    if (altoIn <= 0)
		Logger::getInstance()->info("El alto del personaje es menor o igual a cero. Se elije uno nuevo con el valor de 60");
    if ( zindexIn < 0 )
        Logger::getInstance()->info("El zindex del personaje es menor a cero. Se elije uno nuevo para que el personaje este adelante de todas las capas");
   	if (direccionIn != DIRECCION_PERS_DERECHA && direccionIn != DIRECCION_PERS_IZQUIERDA)	{
		direccionIn = DIRECCION_PERS_DERECHA;
		Logger::getInstance()->info("La configuracion de la direccion del personaje no es la correcta. Se lo dirije en direccion derecha");
	}

	this->ancho = (anchoIn > 0) ? anchoIn : ANCHO_PERS_DEFAULT;
	this->alto = (altoIn > 0) ? altoIn : ALTO_PERS_DEFAULT;
	this->z_index = (zindexIn >= 0) ? zindexIn : Z_INDEX_PERS_DEFAULT;
	this->spritesDef = new list<SpriteDef*>();
	this->direccion = direccionIn;
	this->posicionInicial = posInicial;
	this->colorAlternativoDef = colorAlter;
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

void PersonajeDef::ajustarPosicionIncial(double anchoEscenario, double anchoVentana, double ypiso){
	Vector2f p_posInicial((anchoEscenario/2.0) - this->direccion*(anchoVentana/3.0),ypiso);
	this->posicionInicial = p_posInicial;
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

void PersonajeDef::setDireccion(int nuevaDireccion) {
	direccion = nuevaDireccion;
}

Vector2f PersonajeDef::getPosicionInicial(){
	return posicionInicial;
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

        o<<"PersonajeDef -> [ancho, alto, zindex, direccion,pos_inicial]=[";
        o<<p.ancho<<", "<<p.alto<<", "<<p.z_index<<", "<<p.direccion<<", "<<p.posicionInicial<<"]"<<endl;
        o<<"sprites: {"<<endl;
    	for (list<SpriteDef*>::iterator it_spritesDef = p.getSpritesDef()->begin() ; it_spritesDef !=  p.getSpritesDef()->end(); it_spritesDef++)
    	{
    		o<<**it_spritesDef<<endl;
    	}
    	o<<"}";
    	o<<*p.getColorAlternativoDef();
        return o;
}

int PersonajeDef::getDireccion() const {
	return direccion;
}

void PersonajeDef::agregarSpritesDef(SpriteDef* spriteDef) {
	this->spritesDef->push_back(spriteDef);
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
