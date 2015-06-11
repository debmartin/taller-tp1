/*
 * Mareado.cpp
 *
 *  Created on: 10/6/2015
 *      Author: val
 */

#include "Mareado.h"

#include "../MRUV.h"

#define VELOCIDAD_DESP_HORIZONTAL_SALTANDO 320.0f
#define VELOCIDAD_DESP_VERTICAL 1120.0f
#define VECTOR_GRAVEDAD Vector2f(0, -2600.f)


Mareado::Mareado(Vector2f posInicial, BVH* caja) :
    Estado(new Reposo(posInicial), MAREADO, caja, EN_ESPERA) {
}

Mareado::Mareado(Vector2f posInicial, estado_personaje estado, BVH* caja) :
    Estado(new Reposo(posInicial), estado, caja, EN_ESPERA) {
}

Mareado::~Mareado()
{
    //dtor
}

bool Mareado::estaEsperando(){
    return true;
}
bool Mareado::estaGolpeado(){
    return true;
}

bool Mareado::estaMareado(){
    return true;
}
