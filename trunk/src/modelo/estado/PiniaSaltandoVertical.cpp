/*
 * PiniaSaltandoVertical.cpp
 *
 *  Created on: 13/5/2015
 *      Author: val
 */

#include "PiniaSaltandoVertical.h"
#include "../MRUV.h"

#define VELOCIDAD_DESP_VERTICAL 1120.0f
#define VELOCIDAD_NULA 0.0f
#define VECTOR_GRAVEDAD Vector2f(0, -2600.f)

PiniaSaltandoVertical::PiniaSaltandoVertical(Trayectoria* trayectoriaActual, float tiempoCreacion, BVH* caja) :
    Estado(trayectoriaActual, tiempoCreacion, PINIA_SALTANDO_VERTICAL, caja){
	ataqueEstado = new Ataque(DANIO_PINIA_SALTANDO);
}

PiniaSaltandoVertical::~PiniaSaltandoVertical()
{
    //dtor
}

bool PiniaSaltandoVertical::estaAtacando(){
	return true;
}

bool PiniaSaltandoVertical::estaSaltando(){
    return true;
}

bool PiniaSaltandoVertical::estaSaltandoVertical(){
    return true;
}
