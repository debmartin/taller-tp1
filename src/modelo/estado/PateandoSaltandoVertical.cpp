/*
 * PateandoSaltandoVertical.cpp
 *
 *  Created on: 12/5/2015
 *      Author: val
 */

#include "PateandoSaltandoVertical.h"
#include "../MRUV.h"

#define VELOCIDAD_DESP_VERTICAL 1120.0f
#define VELOCIDAD_NULA 0.0f
#define VECTOR_GRAVEDAD Vector2f(0, -2600.f)

PateandoSaltandoVertical::PateandoSaltandoVertical(Trayectoria* trayectoriaActual, float tiempoDeCreacion, BVH* caja) :
	Estado(trayectoriaActual, tiempoDeCreacion, PATEANDO_SALTANDO_VERTICAL, caja, DEFENDIENDO_AGACHADO) {
	ataqueEstado = new Ataque(DANIO_PATADA_SALTANDO);
}

PateandoSaltandoVertical::~PateandoSaltandoVertical()
{
//dtor
}

bool PateandoSaltandoVertical::estaAtacando(){
	return true;
}

bool PateandoSaltandoVertical::estaSaltando(){
    return true;
}

bool PateandoSaltandoVertical::estaSaltandoVertical(){
    return true;
}

bool PateandoSaltandoVertical(){
	return true;
}

