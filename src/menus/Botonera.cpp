/*
 * Botonera.cpp
 *
 *  Created on: 16/5/2015
 *      Author: ariel
 */

#include "Botonera.h"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_stdinc.h>
#include <iostream>
#include <list>
#include <utility>

#include "../utils/Logger.h"
#include "../vista/Renderizador.h"
#include "Boton.h"
#include "Posicion.h"
#include "Textura.h"

Botonera::Botonera(string tipo, int cant_filas, int cant_columnas, Posicion* posicion, Posicion* posIni_enfocado) {

	this->cant_columnas = cant_columnas;
	this->cant_filas = cant_filas;
	this->posEnfocado = new Posicion(posIni_enfocado->getX(), posIni_enfocado->getY());

	list<string>* idContenidos = new list<string>();
	if ( tipo == "modos" )
	{
		idContenidos->push_back("P1_vs_P2");
		idContenidos->push_back("P1_vs_CPU");
		idContenidos->push_back("Practica");

	}
	else if (tipo == "personajes")
	{
		idContenidos->push_back("sonya");
		idContenidos->push_back("sub-zero");
		idContenidos->push_back("personaje_03");
		idContenidos->push_back("personaje_04");
		idContenidos->push_back("personaje_05");
		idContenidos->push_back("personaje_06");
		idContenidos->push_back("personaje_07");
		idContenidos->push_back("personaje_08");
		idContenidos->push_back("personaje_09");
		idContenidos->push_back("personaje_10");
		idContenidos->push_back("personaje_11");
		idContenidos->push_back("personaje_12");
	}

	list<string>::iterator itIdContenidos = idContenidos->begin();

    this->matriz = new Boton**[this->cant_filas];
	for ( int y = 0 ; y < this->cant_filas ; y++ )
	{
		this->matriz[y] = new Boton*[this->cant_columnas];

		for ( int x = 0 ; x < this->cant_columnas ; x++ )
		{
			Posicion* posicionModelo = new Posicion(x,y);

			// es la posicion de arriba a la izquierda
			Posicion* posicionVista = new Posicion(posicion->getX() + BUTTON_WIDTH * x, posicion->getY() + BUTTON_HEIGHT * y);

			Boton* boton = new Boton(posicionModelo, posicionVista);
			boton->cargarIdContenido(*(itIdContenidos++));

			this->matriz[y][x] = boton;

		}
	}

	this->gButtonSpriteSheetTexture = new Textura();

	this->map_gSpriteClips = new map<int,SDL_Rect>();
	for ( int i = 0 ; i < BUTTON_SPRITE_TOTAL ; i++ )
	{
		SDL_Rect rect;
		rect.x = 0;
		rect.y = i * 127;
		rect.w = BUTTON_WIDTH;
		rect.h = BUTTON_HEIGHT;
		this->map_gSpriteClips->insert ( pair<int,SDL_Rect>(i,rect) );
	}

}

bool Botonera::loadMedia(string path_imagen) {
	//Loading success flag
	bool success = true;
	//Load sprites
	if( !this->gButtonSpriteSheetTexture->loadFromFile(path_imagen) )
	{
		Logger::getInstance()->error("Failed to load button sprite texture!");
		success = false;
	}

	return success;

}

Botonera::~Botonera() {
	this->gButtonSpriteSheetTexture->free();
}

void Botonera::manejarEvento(SDL_Event evento) {

	const Uint8* estadoTeclado = SDL_GetKeyboardState(NULL);
	if (estadoTeclado[SDL_SCANCODE_LEFT])
	{
		if ( this->posEnfocado->getX() > 0 )
		{
			this->posEnfocado->deselegir();
			this->posEnfocado->enfocarIzquierda();
		}
	}
	else if (estadoTeclado[SDL_SCANCODE_RIGHT])
	{
		int cant_cols = this->cant_columnas;
		if ( this->posEnfocado->getX() < (--cant_cols) )
		{
			this->posEnfocado->deselegir();
			this->posEnfocado->enfocarDerecha();
		}

	}
	else if (estadoTeclado[SDL_SCANCODE_UP])
	{
		if ( this->posEnfocado->getY() > 0 )
		{
			this->posEnfocado->deselegir();
			this->posEnfocado->enfocarArriba();
		}
	}
	else if (estadoTeclado[SDL_SCANCODE_DOWN])
	{
		int cant_fils = this->cant_filas;
		if ( this->posEnfocado->getY() < (--cant_fils) )
		{
			this->posEnfocado->deselegir();
			this->posEnfocado->enfocarAbajo();
		}
	}
	else if (estadoTeclado[SDL_SCANCODE_RETURN])
	{
		this->posEnfocado->elegir();
	}

}

int Botonera::getCantColumnas() {
	return this->cant_columnas;
}

void Botonera::actualizarModelo() {

	for ( int y = 0 ; y < this->cant_filas ; y++ )
	{
		for ( int x = 0 ; x < this->cant_columnas ; x++ )
		{
			matriz[y][x]->elegirSprite();

			Posicion* posicionActual = matriz[y][x]->getPosicionModelo();

			if ( posicionActual->getX()==this->posEnfocado->getX() && posicionActual->getY()==this->posEnfocado->getY())
			{
				if ( this->posEnfocado->estoyElegido() )
				{
					matriz[y][x]->getPosicionModelo()->elegir();
					this->elegirIdContenido(matriz[y][x]->getIdContenido());

				}
				else
				{
					matriz[y][x]->getPosicionModelo()->enfocar();
					matriz[y][x]->getPosicionModelo()->deselegir();
				}
			}
			else
			{
				matriz[y][x]->getPosicionModelo()->desenfocar();
				matriz[y][x]->getPosicionModelo()->deselegir();
			}
		}
	}
}

int Botonera::getCantFilas() {
	return this->cant_filas;
}

void Botonera::dibujar() {

	//CLEAR screen
	SDL_SetRenderDrawColor( Renderizador::Instance()->getRenderer(), 0x0F, 0x00, 0x00, 0xFF );
	SDL_RenderClear( Renderizador::Instance()->getRenderer() );

	//RENDER buttons
	for ( int y = 0 ; y < this->cant_filas ; y++ )
	{
		for ( int x = 0 ; x < this->cant_columnas ; x++ )
		{
			matriz[y][x]->render(this->gButtonSpriteSheetTexture, this->map_gSpriteClips);
		}
	}

	//UPDATE screen
	SDL_RenderPresent( Renderizador::Instance()->getRenderer() );
}

void Botonera::elegirIdContenido(string idContenido) {
	this->IdContenidoElegido = idContenido;
}

string Botonera::getIdContenidoElegido() {
	return this->IdContenidoElegido;
}
