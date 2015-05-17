/*
 * PatadaAlta.cpp
 *
 *  Created on: 17/5/2015
 *      Author: val
 */

#include "PatadaAlta.h"
#include "../Reposo.h"

PatadaAlta::PatadaAlta(Vector2f posInicial, BVH* caja) :
    Estado(new Reposo(posInicial), PATEANDO_ALTO, caja) {
    ataqueEstado = new Ataque(DANIO_PATADA_ALTA);
}

PatadaAlta::~PatadaAlta()
{
    //dtor
}

bool PatadaAlta::estaAtacando(){
    return true;
}

bool PatadaAlta::estaDefendiendo(){
    return false;
}

bool PatadaAlta::estaBloqueado(){
    return true;
}
