/*
 * EfectosEspeciales.cpp
 *
 *  Created on: 12/6/2015
 *      Author: val
 */

#include "EfectosEspeciales.h"

#include <iostream>
//#include "VentanaGrafica.h"
//#include "../modelo/Observable.h"
#include <SDL2/SDL.h>
#include <vector>

EfectosEspeciales* EfectosEspeciales::instancia_unica = NULL;

EfectosEspeciales* EfectosEspeciales::Instance()
{
	if (instancia_unica == NULL)
	{
		instancia_unica = new EfectosEspeciales();
	}
	return instancia_unica;
}

EfectosEspeciales::EfectosEspeciales(){
	mapaEfectosEspeciales = new map<string, Efecto*>;
	(*this->mapaEfectosEspeciales)["sangre"] = new EfectoSangre(Vector2f(0,0));
}

bool EfectosEspeciales::init(){
	return true;
}

EfectosEspeciales::~EfectosEspeciales(){}

void EfectosEspeciales::ejecutarEfecto(string id, Vector2f pos){
	((*this->mapaEfectosEspeciales)[id])->ejecutarEfecto(pos);
}

void EfectosEspeciales::dibujar(){
	for (map<std::string, Efecto*>::iterator it = this->mapaEfectosEspeciales->begin() ; it != this->mapaEfectosEspeciales->end(); ++it)
	{
		it->second->dibujar();
	}
}
