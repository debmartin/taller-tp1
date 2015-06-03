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

Botonera::Botonera(string tipo, int cant_filas, int cant_columnas, Posicion* posicion) {

	this->tipo = tipo;
	this->cant_columnas = cant_columnas;
	this->cant_filas = cant_filas;
	this->posicionEnfocadaDelJugador1 = new Posicion();
	this->posicionEnfocadaDelJugador2 = new Posicion();

	this->salirMenu_jugador1 = false;
	this->salirMenu_jugador2 = false;

	list<string>* idContenidos = new list<string>();
	if ( this->tipo == "modos" )
	{
		idContenidos->push_back("P1_vs_P2");
		idContenidos->push_back("P1_vs_CPU");
		idContenidos->push_back("Práctica");

	}
	else if ( this->tipo == "personajes")
	{
		idContenidos->push_back("sonya");
		idContenidos->push_back("sonya");
		idContenidos->push_back("sonya");
		idContenidos->push_back("sonya");
		idContenidos->push_back("sonya");
		idContenidos->push_back("sonya");
		idContenidos->push_back("sonya");
		idContenidos->push_back("sonya");
		idContenidos->push_back("sub-zero");
		idContenidos->push_back("sub-zero");
		idContenidos->push_back("sub-zero");
		idContenidos->push_back("sub-zero");
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

void Botonera::manejarEventoJugador1(SDL_Event evento) {

	const Uint8* estadoTeclado = SDL_GetKeyboardState(NULL);
	if (estadoTeclado[SDL_SCANCODE_LEFT])
	{
		if ( this->posicionEnfocadaDelJugador1->getX() > 0 )
		{
			this->posicionEnfocadaDelJugador1->deselegir();
			this->posicionEnfocadaDelJugador1->enfocarIzquierda();
		}
	}
	else if (estadoTeclado[SDL_SCANCODE_RIGHT])
	{
		int cant_cols = this->cant_columnas;
		if ( this->posicionEnfocadaDelJugador1->getX() < (--cant_cols) )
		{
			this->posicionEnfocadaDelJugador1->deselegir();
			this->posicionEnfocadaDelJugador1->enfocarDerecha();
		}

	}
	else if (estadoTeclado[SDL_SCANCODE_UP])
	{
		if ( this->posicionEnfocadaDelJugador1->getY() > 0 )
		{
			this->posicionEnfocadaDelJugador1->deselegir();
			this->posicionEnfocadaDelJugador1->enfocarArriba();
		}
	}
	else if (estadoTeclado[SDL_SCANCODE_DOWN])
	{
		int cant_fils = this->cant_filas;
		if ( this->posicionEnfocadaDelJugador1->getY() < (--cant_fils) )
		{
			this->posicionEnfocadaDelJugador1->deselegir();
			this->posicionEnfocadaDelJugador1->enfocarAbajo();
		}
	}
	else if (estadoTeclado[SDL_SCANCODE_RETURN])
	{
		this->posicionEnfocadaDelJugador1->elegir();
	}

}

void Botonera::manejarEventoJugador2(SDL_Event evento) {

	const Uint8* estadoTeclado = SDL_GetKeyboardState(NULL);
	if (estadoTeclado[SDL_SCANCODE_A])
	{
		cout<<"SDL_SCANCODE_A"<<endl;
		if ( this->posicionEnfocadaDelJugador2->getX() > 0 )
		{
			this->posicionEnfocadaDelJugador2->deselegir();
			this->posicionEnfocadaDelJugador2->enfocarIzquierda();
		}
	}
	else if (estadoTeclado[SDL_SCANCODE_D])
	{
		cout<<"SDL_SCANCODE_D"<<endl;
		int cant_cols = this->cant_columnas;
		if ( this->posicionEnfocadaDelJugador2->getX() < (--cant_cols) )
		{
			this->posicionEnfocadaDelJugador2->deselegir();
			this->posicionEnfocadaDelJugador2->enfocarDerecha();
		}
	}
	else if (estadoTeclado[SDL_SCANCODE_W])
	{
		cout<<"SDL_SCANCODE_W"<<endl;
		if ( this->posicionEnfocadaDelJugador2->getY() > 0 )
		{
			this->posicionEnfocadaDelJugador2->deselegir();
			this->posicionEnfocadaDelJugador2->enfocarArriba();
		}
	}
	else if (estadoTeclado[SDL_SCANCODE_S])
	{
		cout<<"SDL_SCANCODE_S"<<endl;
		int cant_fils = this->cant_filas;
		if ( this->posicionEnfocadaDelJugador2->getY() < (--cant_fils) )
		{
			this->posicionEnfocadaDelJugador2->deselegir();
			this->posicionEnfocadaDelJugador2->enfocarAbajo();
		}
	}
	else if (estadoTeclado[SDL_SCANCODE_BACKSPACE])
	{
		this->posicionEnfocadaDelJugador2->elegir();
	}

}

int Botonera::getCantColumnas() {
	return this->cant_columnas;
}

void Botonera::actualizarModelo(bool* salirMenu) {

	for ( int y = 0 ; y < this->cant_filas ; y++ )
	{
		for ( int x = 0 ; x < this->cant_columnas ; x++ )
		{
			matriz[y][x]->elegirSprite();

			Posicion* posicionActual = matriz[y][x]->getPosicionModelo();

			// jugador1
			if ( posicionActual->getX()==this->posicionEnfocadaDelJugador1->getX() && posicionActual->getY()==this->posicionEnfocadaDelJugador1->getY())
			{
				if ( this->posicionEnfocadaDelJugador1->estoyElegido() )
				{
					matriz[y][x]->getPosicionModelo()->elegir();
					this->elegirIdContenidoParaJugador1(matriz[y][x]->getIdContenido());
					this->salirMenu_jugador1 = true;
					if ( this->tipo=="modos" )
					{
						this->salirMenu_jugador2 = true;
					}

				}
				else
				{
					matriz[y][x]->getPosicionModelo()->enfocar();
					matriz[y][x]->getPosicionModelo()->deselegir();
				}
			}
			else
			{
				if ( this->tipo=="personajes" && posicionActual->getX()==this->posicionEnfocadaDelJugador2->getX() && posicionActual->getY()==this->posicionEnfocadaDelJugador2->getY())
				{
					if ( this->posicionEnfocadaDelJugador2->estoyElegido() )
					{
						matriz[y][x]->getPosicionModelo()->elegir();
						this->elegirIdContenidoParaJugador2(matriz[y][x]->getIdContenido());
						this->salirMenu_jugador2 = true;

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

			*salirMenu = (this->salirMenu_jugador1 && this->salirMenu_jugador2);
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

void Botonera::setPosicionEnfocadaDelJugador1(Posicion* posicionEnfocadaDelJugador1) {
	this->posicionEnfocadaDelJugador1 = posicionEnfocadaDelJugador1;
}

void Botonera::setPosicionEnfocadaDelJugador2(Posicion* posicionEnfocadaDelJugador2) {
	this->posicionEnfocadaDelJugador2 = posicionEnfocadaDelJugador2;
}

string Botonera::getIdContenidoElegidoParaJugador1(){
	return IdContenidoElegido_paraJugador1;
}

string Botonera::getIdContenidoElegidoParaJugador2(){
	return IdContenidoElegido_paraJugador2;
}

void Botonera::elegirIdContenidoParaJugador1(string idContenido) {
	this->IdContenidoElegido_paraJugador1 = idContenido;
}

void Botonera::elegirIdContenidoParaJugador2(string idContenido) {
	this->IdContenidoElegido_paraJugador2 = idContenido;
}
