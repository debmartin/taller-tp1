/*
 * Muerto.cpp
 *
 *  Created on: 2/6/2015
 *      Author: val
 */

#include "Muerto.h"

Muerto::Muerto(Vector2f posInicial, BVH* caja) :
    Estado(new Reposo(posInicial), MUERTO_EN_PISO, caja, EN_ESPERA) {
}

Muerto::Muerto(Vector2f posInicial, estado_personaje estado,BVH* caja) :
    Estado(new Reposo(posInicial), estado, caja, EN_ESPERA) {
}

Muerto::~Muerto()
{
    //dtor
}

bool Muerto::estaEnPiso(){
    return true;
}

bool Muerto::estaMuerto(){
    return true;
}
