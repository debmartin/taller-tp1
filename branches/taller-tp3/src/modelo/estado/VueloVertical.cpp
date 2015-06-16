/*
 * VueloVertical.cpp
 *
 *  Created on: 14/6/2015
 *      Author: val
 */

#include "VueloVertical.h"
#include "../MRUV.h"

#define VELOCIDAD_DESP_HORIZONTAL 0.0f
#define VELOCIDAD_DESP_VERTICAL 800.0f
#define VECTOR_GRAVEDAD Vector2f(0, 0.f)

VueloVertical::VueloVertical(Vector2f posInicial, estado_personaje estado, BVH* caja) :
    Estado(new MRUV(posInicial, Vector2f(VELOCIDAD_DESP_HORIZONTAL, VELOCIDAD_DESP_VERTICAL), VECTOR_GRAVEDAD), estado, caja, estado) {
}

VueloVertical::VueloVertical(Vector2f posInicial, estado_personaje estado, BVH* caja, float velocidad_vertical) :
    Estado(new MRUV(posInicial, Vector2f(VELOCIDAD_DESP_HORIZONTAL, velocidad_vertical), VECTOR_GRAVEDAD), estado, caja, estado) {
}

VueloVertical::~VueloVertical()
{
    //dtor
}

bool VueloVertical::estaVolandoVertical(){
    return true;
}

bool VueloVertical::haciendoFatality(){
	if(Id() == ANIMALITY2){
		return true;
	}else{
		return false;
	}
}

bool VueloVertical::recibioFatality(){
	if(Id() == RECIBIENDO_GOLPE){
		return true;
	}else{
		return false;
	}
}
