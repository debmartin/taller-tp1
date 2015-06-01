/*
 * PateandoSaltandoDiagonalIzquierda.cpp
 *
 *  Created on: 12/5/2015
 *      Author: val
 */

#include "PateandoSaltandoDiagonalIzquierda.h"

#include "../Reposo.h"
#include "../MRUV.h"

#define VELOCIDAD_DESP_HORIZONTAL_SALTANDO 320.0f
#define VELOCIDAD_DESP_VERTICAL 1120.0f
#define VECTOR_GRAVEDAD Vector2f(0, -2600.f)

PateandoSaltandoDiagonalIzquierda::PateandoSaltandoDiagonalIzquierda(Trayectoria* trayectoriaActual, float tiempoDeCreacion, BVH* caja) :
	Estado(trayectoriaActual, tiempoDeCreacion, PATEANDO_SALTANDO_DIAGONAL_IZQUIERDA, caja) {
	ataqueEstado = new Ataque(DANIO_PATADA_SALTANDO);
}

PateandoSaltandoDiagonalIzquierda::PateandoSaltandoDiagonalIzquierda(Vector2f posInicial, BVH* caja) :
	Estado(new MRUV(posInicial, Vector2f(-VELOCIDAD_DESP_HORIZONTAL_SALTANDO, VELOCIDAD_DESP_VERTICAL), VECTOR_GRAVEDAD), PATEANDO_SALTANDO_DIAGONAL_IZQUIERDA, caja) {
	ataqueEstado = new Ataque(DANIO_PATADA_SALTANDO);
}

PateandoSaltandoDiagonalIzquierda::~PateandoSaltandoDiagonalIzquierda()
{
//dtor
}

bool PateandoSaltandoDiagonalIzquierda::estaAtacando(){
	return true;
}

bool PateandoSaltandoDiagonalIzquierda::estaSaltando(){
    return true;
}

bool PateandoSaltandoDiagonalIzquierda::estaSaltandoDiagonalIzquierda(){
    return true;
}

bool PateandoSaltandoDiagonalIzquierda::ejecutandoMovimientoEspecial(){
    return true;
}
