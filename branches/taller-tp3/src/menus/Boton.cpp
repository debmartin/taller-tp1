/*
 * Boton.cpp
 *
 *  Created on: 16/5/2015
 *      Author: ariel
 */

#include "Boton.h"

#include "Posicion.h"
#include "Textura.h"


Boton::Boton(Posicion* posicionModelo, Posicion* posicionVista) {

	this->posicionModelo = posicionModelo;
	mPosition.x = posicionVista->getX();
	mPosition.y = posicionVista->getY();
	this->elegido = false;
}

Boton::~Boton() {
	// TODO Auto-generated destructor stub
}

Posicion* Boton::getPosicionModelo() const {
	return posicionModelo;
}

ostream& operator <<(ostream &o, const Boton &b) {

        o<<"Boton -> [x,y, idContenido]:["<<b.mPosition.x<<","<<b.mPosition.y<<","<<b.idContenido<<"]";
        return o;
}

void Boton::render(Textura* gButtonSpriteSheetTexture)
{
	//Show current button sprite
	gButtonSpriteSheetTexture->render( mPosition.x, mPosition.y, &this->dimension );
}

string Boton::getIdContenido() const {
	return idContenido;
}

void Boton::cargarIdContenido(string idContenido) {
	this->idContenido = idContenido;
}

void Boton::cargarDimension(SDL_Rect dimension) {
	this->dimension = dimension;
}
