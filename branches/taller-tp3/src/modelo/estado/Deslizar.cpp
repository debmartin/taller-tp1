/*
 * Deslizar.cpp
 *
 *  Created on: 1/6/2015
 *      Author: val
 */

#include "Deslizar.h"

#define VELOCIDAD_DESP_HORIZONTAL_DESLIZANDO 400.0f
#define VELOCIDAD_NULA 0.0f
#define VECTOR_VELOCIDAD_NULA Vector2f(0, 0)
#define D_IZQUIERDA 1

Deslizar::Deslizar(Vector2f posInicial, estado_personaje estado, BVH* caja, bool direccion) :
	Estado((Trayectoria*) new MRU(posInicial, Vector2f(VELOCIDAD_DESP_HORIZONTAL_DESLIZANDO, VELOCIDAD_NULA)), estado, caja, EN_ESPERA) {
	ataqueEstado = new Ataque(DANIO_PATADA_ALTA);
	if(direccion == D_IZQUIERDA)
	    getTrayectoria()->reducirVelocidad(Vector2f(-VELOCIDAD_DESP_HORIZONTAL_DESLIZANDO, VELOCIDAD_NULA));
}

Deslizar::Deslizar(Vector2f posInicial, estado_personaje estado, BVH* caja, bool direccion, float velocidad_horizontal) :
	Estado((Trayectoria*) new MRU(posInicial, Vector2f(velocidad_horizontal, VELOCIDAD_NULA)), estado, caja, EN_ESPERA) {
	ataqueEstado = new Ataque(0);
	if(direccion == D_IZQUIERDA)
	    getTrayectoria()->reducirVelocidad(Vector2f(-velocidad_horizontal, VELOCIDAD_NULA));
}

Deslizar::~Deslizar()
{
    //dtor
}

bool Deslizar::estaAtacando(){
    return true;
}

bool Deslizar::haciendoFatality(){
	if(Id() == ANIMALITY2){
		return true;
	}else{
		return false;
	}
}
