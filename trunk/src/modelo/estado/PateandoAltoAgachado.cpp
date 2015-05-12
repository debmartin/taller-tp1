/*
 * PateandoAltoAgachado.cpp
 *
 *  Created on: 12/5/2015
 *      Author: val
 */

#include "PateandoAltoAgachado.h"

#define DANIO_PATADA 10

PateandoAltoAgachado::PateandoAltoAgachado(Vector2f posInicial, BVH* caja) :
	Estado(new Reposo(posInicial), PATEANDO_ALTO_AGACHADO, caja) {
	ataqueEstado = new Ataque(DANIO_PATADA);
}

PateandoAltoAgachado::~PateandoAltoAgachado() {
	// TODO Auto-generated destructor stub
}

bool PateandoAltoAgachado::estaAtacando(){
    return true;
}

bool PateandoAltoAgachado::estaDefendiendo(){
    return false;
}
