/*
 * Deslizar.cpp
 *
 *  Created on: 1/6/2015
 *      Author: val
 */

#include "Deslizar.h"

#define VELOCIDAD_DESP_HORIZONTAL_CAMINANDO 400.0f
#define VELOCIDAD_DESP_HORIZONTAL_RETROCEDIENDO 150.0f
#define VELOCIDAD_NULA 0.0f
#define VECTOR_VELOCIDAD_NULA Vector2f(0, 0)
#define D_IZQUIERDA 1

Deslizar::Deslizar(Vector2f posInicial, BVH* caja, bool direccion) :
	Estado((Trayectoria*) new MRU(posInicial, Vector2f(VELOCIDAD_DESP_HORIZONTAL_CAMINANDO, VELOCIDAD_NULA)), SLIDE, caja) {
	ataqueEstado = new Ataque(DANIO_PATADA_ALTA);
	if(direccion == D_IZQUIERDA)
	    getTrayectoria()->reducirVelocidad(Vector2f(-VELOCIDAD_DESP_HORIZONTAL_CAMINANDO, VELOCIDAD_NULA));
}

Deslizar::~Deslizar()
{
    //dtor
}

bool Deslizar::estaAtacando(){
    return true;
}
