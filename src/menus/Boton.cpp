/*
 * Boton.cpp
 *
 *  Created on: 16/5/2015
 *      Author: ariel
 */

#include "Boton.h"

#include <string>
#include <utility>

#include "Posicion.h"
#include "Textura.h"


Boton::Boton(Posicion* posicionModelo, Posicion* posicionVista) {

	this->posicionModelo = posicionModelo;
	mPosition.x = posicionVista->getX();
	mPosition.y = posicionVista->getY();
	mCurrentSprite = BUTTON_SPRITE_OUT;
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

void Boton::elegirSprite() {

	if ( this->posicionModelo->estoyEnfocado() )
	{
		mCurrentSprite = BUTTON_SPRITE_OVER_MOTION;
	}
	else
	{
		mCurrentSprite = BUTTON_SPRITE_OUT;
	}

	if ( this->posicionModelo->estoyElegido() )
	{
		mCurrentSprite = BUTTON_SPRITE_DOWN;
	}
}

void Boton::render(Textura* gButtonSpriteSheetTexture, map<int,SDL_Rect>* mapSpriteClips)
{
	//Show current button sprite
	gButtonSpriteSheetTexture->render( mPosition.x, mPosition.y, &mapSpriteClips->find(mCurrentSprite)->second );
}

string Boton::getIdContenido() const {
	return idContenido;
}

void Boton::cargarIdContenido(string idContenido) {
	this->idContenido = idContenido;
}
