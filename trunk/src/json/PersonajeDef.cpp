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

PersonajeDef::PersonajeDef(double ancho, double alto, int zindex, int direccion)
{
	this->ancho = ancho;
	this->alto = alto;
	this->z_index = zindex;
	this->spritesDef = new list<SpriteDef*>;
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

PersonajeDef::~PersonajeDef(){
	// TODO Auto-generated destructor stub
}

list<SpriteDef*>* PersonajeDef::getSpritesDef() const {
	return spritesDef;
}

ostream& operator <<(ostream &o, const PersonajeDef &p) {

        o<<"PersonajeDef -> [ancho, alto, zindex, direccion]=[";
        o<<p.ancho<<", "<<p.alto<<", "<<p.z_index<<", "<<p.direccion<<"]"<<endl;
        o<<"{"<<endl;
    	for (list<SpriteDef*>::iterator it_spritesDef = p.getSpritesDef()->begin() ; it_spritesDef !=  p.getSpritesDef()->end(); it_spritesDef++)
    	{
    		cout<<**it_spritesDef<<endl;
    	}
    	o<<"}";
        return o;
}

int PersonajeDef::getDireccion() const {
	return direccion;
}

void PersonajeDef::agregarSpritesDef(SpriteDef* spriteDef) {
	this->spritesDef->push_back(spriteDef);
}
