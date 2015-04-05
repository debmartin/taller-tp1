/*
 * Observable.cpp
 *
 *  Created on: 5/4/2015
 *      Author: val
 */

#include "Observable.h"
#include <list>

Observable::Observable(){
	this->observadores = new std::list<Observador*>;
}

void Observable::agregarObservador(Observador& unObservador){
	this->observadores->push_back(&unObservador);
}

void Observable::notificarObservadores(){
	std::list<Observador*>::iterator iterador = this->observadores->begin();
	while (iterador != this->observadores->end()){
		(*iterador)->actualizarNotificacion();
	};
}

Observable::~Observable(){}


