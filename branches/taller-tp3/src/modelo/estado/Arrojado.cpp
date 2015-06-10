/*
 * Arrojado.cpp
 *
 *  Created on: 10/6/2015
 *      Author: val
 */

#include "Arrojado.h"

#define VELOCIDAD_DESP_HORIZONTAL_CAMINANDO 400.0f
#define VELOCIDAD_DESP_HORIZONTAL_RETROCEDIENDO 150.0f
#define VELOCIDAD_NULA 0.0f
#define VECTOR_VELOCIDAD_NULA Vector2f(0, 0)
#define D_IZQUIERDA 1

Arrojado::Arrojado(Vector2f posInicial, estado_personaje estado, BVH* caja, bool direccion) :
	Estado((Trayectoria*) new MRU(posInicial, Vector2f(VELOCIDAD_DESP_HORIZONTAL_CAMINANDO, VELOCIDAD_NULA)), estado, caja, EN_ESPERA) {
	if(direccion == D_IZQUIERDA)
	    getTrayectoria()->reducirVelocidad(Vector2f(-VELOCIDAD_DESP_HORIZONTAL_CAMINANDO, VELOCIDAD_NULA));
}

Arrojado::~Arrojado() {
	// TODO Auto-generated destructor stub
}

