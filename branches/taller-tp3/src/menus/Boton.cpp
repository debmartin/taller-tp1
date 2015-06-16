/*
 * Boton.cpp
 *
 *  Created on: 16/5/2015
 *      Author: ariel
 */

#include "Boton.h"

#include "Textura.h"


Boton::Boton(Posicion* posicionModelo, string idContenido, SDL_Rect rectOrigen, SDL_Rect rectDestino) {

	this->posicionModelo = posicionModelo;
	this->idContenido = idContenido;
	this->rectOrigen = rectOrigen;
	this->rectDestino = rectDestino;
	this->elegido = false;
}

Boton::~Boton() {

}

Posicion* Boton::getPosicionModelo() const {
	return posicionModelo;
}

void Boton::render(Textura* gButtonSpriteSheetTexture)
{

	gButtonSpriteSheetTexture->setWidth(this->rectDestino.w);
	gButtonSpriteSheetTexture->setHeight(this->rectDestino.h);

	//Show current button sprite
	gButtonSpriteSheetTexture->render( this->rectDestino.x, this->rectDestino.y, &this->rectOrigen );
}

string Boton::getIdContenido() const {
	return idContenido;
}
