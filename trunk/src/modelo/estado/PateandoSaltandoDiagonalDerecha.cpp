/*
 * PateandoSaltandoDiagonalDerecha.cpp
 *
 *  Created on: 12/5/2015
 *      Author: val
 */

#include "PateandoSaltandoDiagonalDerecha.h"

#include "../Reposo.h"
#include "../MRUV.h"

#define DANIO_PATADA 10
#define VELOCIDAD_DESP_HORIZONTAL_SALTANDO 320.0f
#define VELOCIDAD_DESP_VERTICAL 1120.0f
#define VECTOR_GRAVEDAD Vector2f(0, -2600.f)

PateandoSaltandoDiagonalDerecha::PateandoSaltandoDiagonalDerecha(Vector2f posInicial, BVH* caja) :
	Estado(new MRUV(posInicial, Vector2f(VELOCIDAD_DESP_HORIZONTAL_SALTANDO, VELOCIDAD_DESP_VERTICAL), VECTOR_GRAVEDAD), PATEANDO_SALTANDO_DIAGONAL_DERECHA, caja) {
	ataqueEstado = new Ataque(DANIO_PATADA);
}

PateandoSaltandoDiagonalDerecha::~PateandoSaltandoDiagonalDerecha()
{
//dtor
}

bool PateandoSaltandoDiagonalDerecha::estaAtacando(){
	return true;
}

bool PateandoSaltandoDiagonalDerecha::estaDefendiendo(){
	return false;
}