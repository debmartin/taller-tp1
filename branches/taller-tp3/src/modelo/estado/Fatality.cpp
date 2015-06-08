/*
 * Fatality.cpp
 *
 *  Created on: 7/6/2015
 *      Author: val
 */

#include "Fatality.h"
#include "../Reposo.h"

Fatality::Fatality(Vector2f posInicial, estado_personaje estado, BVH* caja) :
    Estado(new Reposo(posInicial), estado, caja) {
    Logger::getInstance()->debug("Personaje: en fatality.");
}

Fatality::~Fatality()
{
    //dtor
}

bool Fatality::estaEsperando(){
    return true;
}

bool Fatality::haciendoFatality(){
    return true;
}
