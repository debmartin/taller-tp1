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

PiniaSaltandoDiagonalIzquierda::PiniaSaltandoDiagonalIzquierda(Vector2f posInicial, BVH* caja) :
    Estado(new MRUV(posInicial, Vector2f(-VELOCIDAD_DESP_HORIZONTAL_SALTANDO, VELOCIDAD_DESP_VERTICAL), VECTOR_GRAVEDAD), SALTANDO_OBLICUO_IZQUIERDA, caja){
    //ctor
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

bool PiniaSaltandoDiagonalIzquierda::estaSaltandoDiagonal(){
    return true;
}
