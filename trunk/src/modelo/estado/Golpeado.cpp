/*
 * Golpeado.cpp
 *
 *  Created on: 22/5/2015
 *      Author: val
 */

#include "Golpeado.h"

Golpeado::Golpeado(Vector2f posInicial, BVH* caja) :
    Estado(new Reposo(posInicial), RECIBIENDO_GOLPE, caja) {
}

Golpeado::~Golpeado()
{
    //dtor
}

bool Golpeado::estaEsperando(){
    return true;
}
