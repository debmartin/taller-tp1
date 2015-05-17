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

PiniaSaltandoDiagonalDerecha::PiniaSaltandoDiagonalDerecha(Trayectoria* trayectoriaActual, float tiempoDeCreacion, BVH* caja) :
	Estado(trayectoriaActual, tiempoDeCreacion, PINIA_SALTANDO_DIAGONAL_DERECHA, caja){
	ataqueEstado = new Ataque(DANIO_PINIA_SALTANDO);
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
