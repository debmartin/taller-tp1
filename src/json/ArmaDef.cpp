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

ArmaDef::ArmaDef(SpriteDef* unArma, int velocidad) {
	this->spriteArma = unArma;
	this->velocidadArma = velocidad;
}

SpriteDef* ArmaDef::getSpriteDefArma(){
	return spriteArma;
}

int ArmaDef::getVelocidad(){
	return velocidadArma;
}

ArmaDef::~ArmaDef() {
	// TODO Auto-generated destructor stub
}

