/*
 * Golpeado.cpp
 *
 *  Created on: 22/5/2015
 *      Author: val
 */

#include "Golpeado.h"
#include "../MRUV.h"

#define VELOCIDAD_DESP_HORIZONTAL_SALTANDO 320.0f
#define VELOCIDAD_DESP_VERTICAL 1120.0f
#define VECTOR_GRAVEDAD Vector2f(0, -2600.f)


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
