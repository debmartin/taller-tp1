/*
 * Observable.cpp
 *
 *  Created on: 5/4/2015
 *      Author: val
 */

#include "Observable.h"
#include <iostream>
using namespace std;

Observable::Observable(){
	this->observadores = new std::list<Observador*>;
}

void Observable::agregarObservador(Observador* unObservador){
	this->observadores->push_back(unObservador);
}

void Observable::notificarObservadores(){
	cout<<"Observable:notificar observador"<<endl;

	for(std::list<Observador*>::iterator iterador = this->observadores->begin(); iterador != this->observadores->end(); ++iterador)
	{
		cout<<"Itero lista de Observadores"<<endl;
		(*iterador)->recibirNotificacion(this);
	}

}



Observable::~Observable(){
    delete observadores;
}


