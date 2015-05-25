/*
 * GolpeadoCaidaDerecha.cpp
 *
 *  Created on: 24/5/2015
 *      Author: val
 */

#include "GolpeadoCaidaDerecha.h"
#include "../MRUV.h"

#define VELOCIDAD_DESP_HORIZONTAL_SALTANDO 320.0f
#define VELOCIDAD_DESP_VERTICAL 1120.0f
#define VECTOR_GRAVEDAD Vector2f(0, -2600.f)

GolpeadoCaidaDerecha::GolpeadoCaidaDerecha(Vector2f posInicial, BVH* caja) :
    Estado(new MRUV(posInicial, Vector2f(VELOCIDAD_DESP_HORIZONTAL_SALTANDO, VELOCIDAD_DESP_VERTICAL), VECTOR_GRAVEDAD), RECIBIENDO_GOLPE_CAIDA, caja){
}

GolpeadoCaidaDerecha::~GolpeadoCaidaDerecha()
{
    //dtor
}

bool GolpeadoCaidaDerecha::estaSaltando(){
    return true;
}

bool GolpeadoCaidaDerecha::estaSaltandoDiagonalDerecha(){
    return true;
}
