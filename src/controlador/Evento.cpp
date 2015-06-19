/*
 * Evento.cpp
 *
 *  Created on: 18/6/2015
 *      Author: gaston
 */

#include "Evento.h"

Evento::Evento() {
	this->coloreado = false;
	this->nombre = "ERROR";
	cout << "ERROR: Evento::Evento() > No debe usarse constructor por defecto" << endl;
}

Evento::Evento(string nombreEvento) {
	this->coloreado = false;
	this->nombre = nombreEvento;
}

void Evento::colorear() {
	this->coloreado = true;
}

void Evento::descolorear() {
	this->coloreado = false;
}

bool Evento::estaColoreado() {
	return this->coloreado;
}

string Evento::getNombre() {
	return this->nombre;
}

Evento::~Evento() { }

