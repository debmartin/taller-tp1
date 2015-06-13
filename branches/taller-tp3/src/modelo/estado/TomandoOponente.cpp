/*
 * TomandoOponente.cpp
 *
 *  Created on: 12/6/2015
 *      Author: val
 */

#include "TomandoOponente.h"
#include "../Reposo.h"

TomandoOponente::TomandoOponente(Vector2f posInicial, estado_personaje estado,BVH* caja) :
    Estado(new Reposo(posInicial), estado, caja, PATEANDO_ALTO) {
	ataqueEstado = new Ataque(DANIO_PINIA_ALTA);
}

TomandoOponente::~TomandoOponente()
{
    //dtor
}

bool TomandoOponente::estaTomandoAlOponente(){
	return true;
}

bool TomandoOponente::ejecutandoMovimientoEspecial(){
	return true;
}

bool TomandoOponente::estaAtacando(){
	return true;
}
