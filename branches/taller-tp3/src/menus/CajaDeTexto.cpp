/*
 * CajaDeTexto.cpp
 *
 *  Created on: 10/6/2015
 *      Author: ariel
 */

#include "CajaDeTexto.h"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

#include "../utils/Logger.h"
#include "../vista/Renderizador.h"
#include "Textura.h"

CajaDeTexto::CajaDeTexto(int cant_caracteres, int pos_x, int pos_y) {

	this->cant_caracteres = cant_caracteres;
	this->pos_x = pos_x;
	this->pos_y = pos_y;
	this->alto = 30;
	this->ancho = (cant_caracteres * this->alto) / 2;
	this->textura = new Textura();
	this->textColor = { 0xFF, 0, 0, 0xFF };
	this->enfocado = false;
	this->texto = "";
}

CajaDeTexto::~CajaDeTexto() {
	delete this->textura;
}

bool CajaDeTexto::manejarEvento(SDL_Event e) {
	bool renderText = false;

	this->enfocado = false;
	//Get mouse position
	int x, y;
	SDL_GetMouseState( &x, &y );

	if( x > pos_x && x < (pos_x+ancho) && y > pos_y && y < (pos_y+alto))
	{
		this->enfocado = true;
	}

	if ( this->enfocado )
	{
		//Special key input
		if( e.type == SDL_KEYDOWN )
		{
			//Handle backspace
			if( e.key.keysym.sym == SDLK_BACKSPACE && this->texto.length() > 0 )
			{
				//lop off character
				this->texto.erase(this->texto.length()-1,1);
				renderText = true;
			}
		}
		//Special text input event
		else if( e.type == SDL_TEXTINPUT )
		{
			//Append character
			if ( this->texto.length() < this->cant_caracteres)
				this->texto += e.text.text;
			renderText = true;
		}
	}
	return renderText;
}

void CajaDeTexto::dibujar(bool renderText) {

	if( renderText )
	{
		if( this->texto != "" )
		{
			this->textura->loadFromRenderedText( this->texto.c_str(), this->textColor );
		}else{
			this->textura->loadFromRenderedText( " ", this->textColor );
		}
	}

	//dibujar un cuadro blanco y despues el texto
	SDL_Rect fillRect = { this->pos_x, this->pos_y, this->ancho, this->alto };
	SDL_SetRenderDrawColor( Renderizador::Instance()->getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderFillRect( Renderizador::Instance()->getRenderer(), &fillRect );

	//Render text textures
	this->textura->render(this->pos_x, this->pos_y);

}

bool CajaDeTexto::loadMedia() {
	//Loading success flag
	bool success = true;

	//Open the font
	TTF_Font* gFont = TTF_OpenFont( "RECURSOS/lazy.ttf", this->alto );
	this->textura->setFont(gFont);

	if( gFont == NULL )
	{
		Logger::getInstance()->error("Failed to load lazy font! SDL_ttf Error");
		success = false;
	}

	return success;
}

string CajaDeTexto::getTexto() const {
	return texto;
}

bool CajaDeTexto::estoyEnfocado() {
	return this->enfocado;
}
