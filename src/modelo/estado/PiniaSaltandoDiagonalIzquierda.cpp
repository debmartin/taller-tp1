/*
 * PiniaSaltandoDiagonalIzquierda.cpp
 *
 *  Created on: 13/5/2015
 *      Author: val
 */

#include "PiniaSaltandoDiagonalIzquierda.h"
#include "../MRUV.h"

#define VELOCIDAD_DESP_HORIZONTAL_SALTANDO 320.0f
#define VELOCIDAD_DESP_VERTICAL 1120.0f
#define VECTOR_GRAVEDAD Vector2f(0, -2600.f)

PiniaSaltandoDiagonalIzquierda::PiniaSaltandoDiagonalIzquierda(Trayectoria* trayectoriaActual, float tiempoCreacion, BVH* caja) :
    Estado(trayectoriaActual, tiempoCreacion, PINIA_SALTANDO_DIAGONAL_IZQUIERDA, caja){
	ataqueEstado = new Ataque(DANIO_PINIA_SALTANDO);
}

PiniaSaltandoDiagonalIzquierda::~PiniaSaltandoDiagonalIzquierda()
{
    //dtor
}

bool PiniaSaltandoDiagonalIzquierda::estaAtacando(){
	return true;
}

bool PiniaSaltandoDiagonalIzquierda::estaSaltando(){
    return true;
}

bool PiniaSaltandoDiagonalIzquierda::estaSaltandoDiagonalIzquierda(){
    return true;
}
