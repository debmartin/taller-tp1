/*
 * Pantalla.cpp
 *
 *  Created on: 30/5/2015
 *      Author: ariel
 */

#include "Pantalla.h"

#include "../utils/Logger.h"
#include "Botonera.h"
#include "Textura.h"

Pantalla::Pantalla(int anchopx, int altopx, string tipoDeControl_jugador1,
		string tipoDeControl_jugador2) {
	this->tipoDeControl_jugador1 = tipoDeControl_jugador1;
	this->tipoDeControl_jugador2 = tipoDeControl_jugador2;
	this->anchopx = anchopx;
	this->altopx = altopx;
	this->salir = false;
	this->botonera = new Botonera();
	this->fondoPantalla = new Textura();
}

Pantalla::~Pantalla() {
	// TODO Auto-generated destructor stub
}

string Pantalla::getTipoDeControlJugador1() const {
	return tipoDeControl_jugador1;
}

string Pantalla::getTipoDeControlJugador2() const {
	return tipoDeControl_jugador2;
}

int Pantalla::getAnchopx() const {
	return anchopx;
}

int Pantalla::getAltopx() const {
	return altopx;
}

Textura* Pantalla::getFondoPantalla() const {
	return fondoPantalla;
}

bool Pantalla::loadMedia(string path_imagen) {
	//Loading success flag
	bool success = true;
	//Load sprites
	if( !this->fondoPantalla->loadFromFile(path_imagen) )
	{
		Logger::getInstance()->error("Failed to load fondo pantalla!");
		success = false;
	}

	return success;
}

void Pantalla::dibujarFondoPantalla() {

	this->fondoPantalla->setWidth(anchopx);
	this->fondoPantalla->setHeight(altopx);
	this->fondoPantalla->render(0,0);
}
