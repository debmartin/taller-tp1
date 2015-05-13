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

PiniaSaltandoVertical::PiniaSaltandoVertical(Vector2f posInicial, BVH* caja) :
    Estado(new MRUV(posInicial, Vector2f(VELOCIDAD_NULA, VELOCIDAD_DESP_VERTICAL), VECTOR_GRAVEDAD), SALTANDO_VERTICAL, caja){
    //ctor
}

PiniaSaltandoVertical::~PiniaSaltandoVertical()
{
    //dtor
}

bool PiniaSaltandoVertical::estaSaltando(){
    return true;
}
