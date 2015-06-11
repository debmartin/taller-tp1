/*
 * CajaDeTexto.cpp
 *
 *  Created on: 10/6/2015
 *      Author: ariel
 */

#include "CajaDeTexto.h"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

#include "../utils/Logger.h"
#include "../vista/Renderizador.h"
#include "Textura.h"

CajaDeTexto::CajaDeTexto(int cant_caracteres, int pos_x, int pos_y) {

	this->cant_caracteres = cant_caracteres;
	this->pos_x = pos_x;
	this->pos_y = pos_y;
	this->textura = new Textura();
	this->textColor = { 0, 0, 0, 0xFF };
}

CajaDeTexto::~CajaDeTexto() {
	delete this->textura;
}

bool CajaDeTexto::manejarEvento(string* inputText, SDL_Event e) {
	bool renderText = false;

	//Special key input
	if( e.type == SDL_KEYDOWN )
	{
		//Handle backspace
		if( e.key.keysym.sym == SDLK_BACKSPACE && (*inputText).length() > 0 )
		{
			//lop off character
			(*inputText).erase((*inputText).length()-1,1);
			renderText = true;
		}
	}
	//Special text input event
	else if( e.type == SDL_TEXTINPUT )
	{
		//Append character
		if ( (*inputText).length() < this->cant_caracteres)
			*inputText += e.text.text;
		renderText = true;
	}

	return renderText;
}

void CajaDeTexto::dibujar(bool renderText, string inputText) {

	//CLEAR screen
	SDL_SetRenderDrawColor( Renderizador::Instance()->getRenderer(), 0x0F, 0x00, 0x00, 0xFF );
	SDL_RenderClear( Renderizador::Instance()->getRenderer() );

	if( renderText )
	{
		if( inputText != "" )
		{
			this->textura->loadFromRenderedText( inputText.c_str(), this->textColor );
		}else{
			this->textura->loadFromRenderedText( " ", this->textColor );
		}
	}

	//Render text textures
	this->textura->render(this->pos_x, this->pos_y);

	//UPDATE screen
	SDL_RenderPresent( Renderizador::Instance()->getRenderer() );
}

bool CajaDeTexto::loadMedia() {
	//Loading success flag
	bool success = true;

	//Open the font
	TTF_Font* gFont = TTF_OpenFont( "RECURSOS/lazy.ttf", 28 );
	this->textura->setFont(gFont);

	if( gFont == NULL )
	{
		Logger::getInstance()->error("Failed to load lazy font! SDL_ttf Error");
		success = false;
	}

	return success;
}
