/*
 * PatadaBaja.cpp
 *
 *  Created on: 17/5/2015
 *      Author: val
 */

#include "PatadaBaja.h"
#include "../Reposo.h"

PatadaBaja::PatadaBaja(Vector2f posInicial, BVH* caja) :
    Estado(new Reposo(posInicial), PATEANDO_ALTO, caja) {
    ataqueEstado = new Ataque(DANIO_PATADA_BAJA);
}

PatadaBaja::~PatadaBaja()
{
    //dtor
}

bool PatadaBaja::estaAtacando(){
    return true;
}

bool PatadaBaja::estaDefendiendo(){
    return false;
}

bool PatadaBaja::estaBloqueado(){
    return true;
}
