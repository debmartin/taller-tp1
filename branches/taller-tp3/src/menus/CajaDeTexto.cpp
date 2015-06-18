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

CajaDeTexto::CajaDeTexto() {

}

CajaDeTexto::CajaDeTexto(int cant_caracteres, int pos_x, int pos_y) {

	this->cant_caracteres = cant_caracteres;
	this->cant_caracteres_vista = 9;
	this->pos_x = pos_x;
	this->pos_y = pos_y;
	this->alto = 30;
	this->ancho = (this->cant_caracteres_vista * this->alto) / 2;
	this->textura = new Textura();
	this->textColor = { 0, 0, 0, 0xFF };
	this->enfocado = false;
	this->texto = "";
	this->textoMemoria = "";
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
			int posicion = 0;
			//Handle backspace
			if( e.key.keysym.sym == SDLK_BACKSPACE && this->textoMemoria.length() > 0 )
			{
				//lop off character

				//cout<<"Se borra un caracter:"<<endl;
				if(this->textoMemoria.length() == 0){

				}else if(this->textoMemoria.length() <= this->cant_caracteres_vista){
					this->textoMemoria = this->textoMemoria.substr(0,this->textoMemoria.length()-1);

					//Texto vista
					this->texto = this->textoMemoria;

				}else{
					this->textoMemoria = this->textoMemoria.substr(0,this->textoMemoria.length()-1);

					//Texto vista
					this->texto = this->textoMemoria.substr(this->textoMemoria.length()-this->cant_caracteres_vista,this->cant_caracteres_vista);
				}
				/*
				cout<<"Texto en memoria:"<<endl;
				cout<<this->textoMemoria<<endl;
				cout<<"Vista:"<<endl;
				cout<<this->texto<<endl;
				*/
				renderText = true;
			}
		}
		//Special text input event
		else if( e.type == SDL_TEXTINPUT )
		{

			//Append character
			if ( this->textoMemoria.length() < this->cant_caracteres)
			{
				//cout<<"Ingresa caracter"<<endl;
				this->textoMemoria += e.text.text;

				if(this->textoMemoria.length() <= this->cant_caracteres_vista){
					this->texto = this->textoMemoria;
				}
				else if ( this->textoMemoria.length() <= this->cant_caracteres )
				{
					this->texto = this->textoMemoria.substr(this->textoMemoria.length()-this->cant_caracteres_vista,this->textoMemoria.length());
				}
				/*
				cout<<"Texto en memoria:"<<endl;
				cout<<this->textoMemoria<<endl;

				cout<<"Vista:"<<endl;
				cout<<this->texto<<endl;*/
			}

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

	SDL_Rect fillRect2 = { this->pos_x, this->pos_y, this->ancho/9, this->alto };
	SDL_SetRenderDrawColor( Renderizador::Instance()->getRenderer(), 32, 178, 170, 0 );
	SDL_RenderFillRect( Renderizador::Instance()->getRenderer(), &fillRect2 );
	//Render text textures
	this->textura->render(this->pos_x, this->pos_y);

}

bool CajaDeTexto::loadMedia() {
	//Loading success flag
	bool success = true;

	//Open the font
	TTF_Font* gFont = TTF_OpenFont( "RECURSOS/HUD/mk2.ttf", this->alto );
	//TTF_Font* gFont = TTF_OpenFont( "RECURSOS/lazy.ttf", this->alto );
	this->textura->setFont(gFont);

	if( gFont == NULL )
	{
		Logger::getInstance()->error("Failed to load lazy font! SDL_ttf Error");
		success = false;
	}

	return success;
}

string CajaDeTexto::getTexto() const {
	return textoMemoria;
}

bool CajaDeTexto::estoyEnfocado() {
	return this->enfocado;
}

void CajaDeTexto::setTexto(string texto) {
	this->texto = texto;
	this->textoMemoria = texto;
}
