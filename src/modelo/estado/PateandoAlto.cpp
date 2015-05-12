/*
 * PateandoAlto.cpp
 *
 *  Created on: 12/5/2015
 *      Author: val
 */

#include "PateandoAlto.h"
#include "../Reposo.h"

#define DANIO_PATADA_BAJA 10

PateandoAlto::PateandoAlto(Vector2f posInicial, BVH* caja) :
    Estado(new Reposo(posInicial), PATEANDO_ALTO, caja) {
    ataqueEstado = new Ataque(DANIO_PATADA_BAJA);
}

PateandoAlto::~PateandoAlto()
{
    //dtor
}

bool PateandoAlto::estaAtacando(){
    return true;
}

bool PateandoAlto::estaDefendiendo(){
    return false;
}

