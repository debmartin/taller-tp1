/*
 * ArmaDef.cpp
 *
 *  Created on: 9/5/2015
 *      Author: val
 */

#include "ArmaDef.h"

ArmaDef::ArmaDef() {
	// TODO Auto-generated constructor stub

}

ArmaDef::ArmaDef(SpriteDef* unArma, int velocidad, double ancho, double alto) {
	this->spriteArma = unArma;
	this->velocidadArma = velocidad;
	this->ancho = ancho;
	this->alto = alto;
}

SpriteDef* ArmaDef::getSpriteDefArma(){
	return spriteArma;
}

double ArmaDef::getAlto(){
	return alto;
}

double ArmaDef::getAncho(){
	return ancho;
}

int ArmaDef::getVelocidad(){
	return velocidadArma;
}

ArmaDef::~ArmaDef() {
	// TODO Auto-generated destructor stub
}

