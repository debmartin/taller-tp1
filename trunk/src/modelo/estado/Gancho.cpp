/*
 * Gancho.cpp
 *
 *  Created on: 12/5/2015
 *      Author: val
 */

#include "Gancho.h"
#include "../Reposo.h"

Gancho::Gancho(Vector2f posInicial, BVH* caja) :
    Estado(new Reposo(posInicial), GANCHO, caja) {
	ataqueEstado = new Ataque(DANIO_GANCHO);
}

Gancho::~Gancho()
{
    //dtor
}

bool Gancho::estaAtacando(){
	return true;
}

bool Gancho::estaDefendiendo(){
	return false;
}
