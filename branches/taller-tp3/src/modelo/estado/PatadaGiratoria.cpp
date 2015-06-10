/*
 * PatadaGiratoria.cpp
 *
 *  Created on: 10/6/2015
 *      Author: val
 */

#include "PatadaGiratoria.h"

PatadaGiratoria::PatadaGiratoria(Vector2f posInicial, BVH* caja) :
	Estado(new Reposo(posInicial), PATADA_GIRATORIA, caja, PATEANDO_BAJO) {
	ataqueEstado = new Ataque(DANIO_PATADA_SALTANDO);
}

PatadaGiratoria::~PatadaGiratoria() {
	// TODO Auto-generated destructor stub
}

bool PatadaGiratoria::estaAtacando(){
    return true;
}

bool PatadaGiratoria::estaAgachado(){
    return true;
}

bool PatadaGiratoria::ejecutandoMovimientoEspecial(){
    return true;
}

bool PatadaGiratoria::efectuandoPatadaGiratoria(){
	return true;
}
