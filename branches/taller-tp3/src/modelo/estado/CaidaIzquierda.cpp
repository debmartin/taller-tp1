/*
 * CaidaIzquierda.cpp
 *
 *  Created on: 28/5/2015
 *      Author: val
 */

#include "CaidaIzquierda.h"
#include "../MRUV.h"

#define VELOCIDAD_DESP_HORIZONTAL_SALTANDO 320.0f
#define VELOCIDAD_DESP_VERTICAL 1120.0f
#define VECTOR_GRAVEDAD Vector2f(0, -2600.f)

CaidaIzquierda::CaidaIzquierda(Vector2f posInicial, BVH* caja) :
    Estado(new MRUV(posInicial, Vector2f(-VELOCIDAD_DESP_HORIZONTAL_SALTANDO, VELOCIDAD_DESP_VERTICAL), VECTOR_GRAVEDAD), CAIDA_IZQUIERDA, caja){
	//ctor
}

CaidaIzquierda::CaidaIzquierda(Vector2f posInicial, float velocidadEnY, BVH* caja) :
    Estado(new MRUV(posInicial, Vector2f(-VELOCIDAD_DESP_HORIZONTAL_SALTANDO, velocidadEnY), VECTOR_GRAVEDAD), CAIDA_IZQUIERDA, caja){
	//ctor
}

CaidaIzquierda::CaidaIzquierda(Vector2f posInicial, estado_personaje estado , BVH* caja) :
    Estado(new MRUV(posInicial, Vector2f(-VELOCIDAD_DESP_HORIZONTAL_SALTANDO, VELOCIDAD_DESP_VERTICAL), VECTOR_GRAVEDAD), estado, caja){
}

CaidaIzquierda::~CaidaIzquierda()
{
    //dtor
}

bool CaidaIzquierda::estaSaltando(){
    return true;
}

bool CaidaIzquierda::estaSaltandoDiagonalIzquierda(){
    return true;
}

bool CaidaIzquierda::estaEnCaida(){
    return true;
}
