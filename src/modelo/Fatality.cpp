/*
 * Fatality.cpp
 *
 *  Created on: 10/6/2015
 *      Author: Juan
 */

#include "Fatality.h"
#ifndef NULL
#define NULL 0;

Fatality::Fatality(Personaje* unoponente, Personaje* unpersonaje,Cola* movimientos) {
	this->Movimientos=movimientos;
	this->Oponente=unoponente;
	this->Ejecutante=unpersonaje;
}

Fatality::~Fatality() {
	this->Oponente=NULL;
	this->Ejecutante=NULL;
	delete Movimientos;
}

void Fatality::Ejecutar()
{
	while (!(this->Movimientos->estaVacia()))
	{
		Orden* movimientoactual=this->Movimientos->pop();
		movimientoactual->Ejecutar();
	};
}
#endif
