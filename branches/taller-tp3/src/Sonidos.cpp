/*
 * Sonidos.cpp
 *
 *  Created on: 5/6/2015
 *      Author: ariel
 */

#include "Sonidos.h"

#include <utility>

Sonidos* Sonidos::sonidos = NULL;

Sonidos::Sonidos() {
	this->mapaSonidos = new map<string,Sonido*>();

}

Sonidos* Sonidos::getInstancia(){
	if ( Sonidos::sonidos  == NULL )
		Sonidos::sonidos = new Sonidos();
	return Sonidos::sonidos;
}

void Sonidos::reproducirSonido(string idSonido)
{
    this->mapaSonidos->find(idSonido)->second->reproducir();
}

void Sonidos::agregar(string idSonido, Sonido* sonido) {
	(*this->mapaSonidos)[idSonido] = sonido;
}

Sonidos::~Sonidos() {
	// TODO Auto-generated destructor stub
}

