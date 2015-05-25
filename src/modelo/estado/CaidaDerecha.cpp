/*
 * CaidaDerecha.cpp
 *
 *  Created on: 28/5/2015
 *      Author: val
 */

#include "CaidaDerecha.h"
#include "../MRUV.h"

#define VELOCIDAD_DESP_HORIZONTAL_SALTANDO 320.0f
#define VELOCIDAD_DESP_VERTICAL 1120.0f
#define VECTOR_GRAVEDAD Vector2f(0, -2600.f)


CaidaDerecha::CaidaDerecha(Vector2f posInicial, BVH* caja) :
    Estado(new MRUV(posInicial, Vector2f(VELOCIDAD_DESP_HORIZONTAL_SALTANDO, VELOCIDAD_DESP_VERTICAL), VECTOR_GRAVEDAD), RECIBIENDO_GOLPE_CAIDA, caja){
}

CaidaDerecha::CaidaDerecha(Vector2f posInicial, estado_personaje estado , BVH* caja) :
    Estado(new MRUV(posInicial, Vector2f(VELOCIDAD_DESP_HORIZONTAL_SALTANDO, VELOCIDAD_DESP_VERTICAL), VECTOR_GRAVEDAD), estado, caja){
}

CaidaDerecha::~CaidaDerecha()
{
    //dtor
}

bool CaidaDerecha::estaSaltando(){
    return true;
}

bool CaidaDerecha::estaSaltandoDiagonalDerecha(){
    return true;
}
