/*
 * PiniaSaltandoDiagonalDerecha.cpp
 *
 *  Created on: 13/5/2015
 *      Author: val
 */

#include "PiniaSaltandoDiagonalDerecha.h"
#include "../MRUV.h"

#define VELOCIDAD_DESP_HORIZONTAL_SALTANDO 320.0f
#define VELOCIDAD_DESP_VERTICAL 1120.0f
#define VECTOR_GRAVEDAD Vector2f(0, -2600.f)

PiniaSaltandoDiagonalDerecha::PiniaSaltandoDiagonalDerecha(Trayectoria* trayectoriaActual, BVH* caja) :
	Estado(trayectoriaActual, PINIA_SALTANDO_DIAGONAL_DERECHA, caja){
}

PiniaSaltandoDiagonalDerecha::PiniaSaltandoDiagonalDerecha(Vector2f posInicial, BVH* caja) :
	Estado(new MRUV(posInicial, Vector2f(VELOCIDAD_DESP_HORIZONTAL_SALTANDO, VELOCIDAD_DESP_VERTICAL), VECTOR_GRAVEDAD), PINIA_SALTANDO_DIAGONAL_DERECHA, caja){
}

PiniaSaltandoDiagonalDerecha::~PiniaSaltandoDiagonalDerecha()
{
//dtor
}

bool PiniaSaltandoDiagonalDerecha::estaAtacando(){
	return true;
}

bool PiniaSaltandoDiagonalDerecha::estaSaltando(){
	return true;
}

bool PiniaSaltandoDiagonalDerecha::estaSaltandoDiagonalDerecha(){
	return true;
}
