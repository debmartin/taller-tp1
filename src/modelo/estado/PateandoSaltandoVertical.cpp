/*
 * PateandoSaltandoVertical.cpp
 *
 *  Created on: 12/5/2015
 *      Author: val
 */

#include "PateandoSaltandoVertical.h"
#include "../Reposo.h"
#include "../MRUV.h"

#define DANIO_PATADA 10
#define VELOCIDAD_DESP_VERTICAL 1120.0f
#define VELOCIDAD_NULA 0.0f
#define VECTOR_GRAVEDAD Vector2f(0, -2600.f)

PateandoSaltandoVertical::PateandoSaltandoVertical(Vector2f posInicial, BVH* caja) :
	Estado(new MRUV(posInicial, Vector2f(VELOCIDAD_NULA, VELOCIDAD_DESP_VERTICAL), VECTOR_GRAVEDAD), PATEANDO_SALTANDO_VERTICAL, caja) {
	ataqueEstado = new Ataque(DANIO_PATADA);
}

PateandoSaltandoVertical::~PateandoSaltandoVertical()
{
//dtor
}

bool PateandoSaltandoVertical::estaAtacando(){
	return true;
}

bool PateandoSaltandoVertical::estaDefendiendo(){
	return false;
}

bool PateandoSaltandoVertical::estaSaltando(){
    return true;
}

bool PateandoSaltandoVertical::estaSaltandoVertical(){
    return true;
}
