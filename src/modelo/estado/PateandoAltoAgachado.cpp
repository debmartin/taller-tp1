/*
 * PateandoAltoAgachado.cpp
 *
 *  Created on: 12/5/2015
 *      Author: val
 */

#include "PateandoAltoAgachado.h"

PateandoAltoAgachado::PateandoAltoAgachado(Vector2f posInicial, BVH* caja) :
	Estado(new Reposo(posInicial), PATEANDO_ALTO_AGACHADO, caja) {
	ataqueEstado = new Ataque(DANIO_PATADA_SALTANDO);
}

PateandoAltoAgachado::~PateandoAltoAgachado() {
	// TODO Auto-generated destructor stub
}

bool PateandoAltoAgachado::estaAtacando(){
    return true;
}

bool PateandoAltoAgachado::estaAgachado(){
    return true;
}
