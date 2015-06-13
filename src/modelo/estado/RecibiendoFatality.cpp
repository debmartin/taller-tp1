/*
 * RecibiendoFatality.cpp
 *
 *  Created on: 13/6/2015
 *      Author: val
 */

#include "RecibiendoFatality.h"

#include "../Reposo.h"

RecibiendoFatality::RecibiendoFatality(Vector2f posInicial, estado_personaje estado, BVH* caja) :
    Estado(new Reposo(posInicial), estado, caja, EN_ESPERA) {
    Logger::getInstance()->debug("Personaje: en fatality.");
}

RecibiendoFatality::~RecibiendoFatality()
{
    //dtor
}

bool RecibiendoFatality::estaEsperando(){
    return true;
}

bool RecibiendoFatality::recibioFatality(){
    return true;
}

bool RecibiendoFatality::ejecutandoMovimientoEspecial(){
	return true;
}
