/*
 * Botonera.cpp
 *
 *  Created on: 16/5/2015
 *      Author: ariel
 */

#include "Botonera.h"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_rect.h>
#include <list>

#include "../controlador/ControladorJoystickMenu.h"
#include "../utils/Logger.h"
#include "Boton.h"
#include "ControladorBotonera.h"
#include "Posicion.h"
#include "Textura.h"

const int ANCHO_FISICO_MODO = 351;
const int ALTO_FISICO_MODO = 174;
const int ANCHO_FISICO_PERSONAJE = 473;
const int ALTO_FISICO_PERSONAJE = 381;

Botonera::Botonera() {

}

Botonera::Botonera(string tipo, int anchopx, int altopx, int cant_filas, int cant_columnas, Posicion* posicion,
					string tipoDeControl_jugador1, string tipoDeControl_jugador2, string modo_juego_elegido) {

	this->tipo = tipo;
	this->cant_columnas = cant_columnas;
	this->cant_filas = cant_filas;
	this->posicionEnfocadaDelJugador1 = new Posicion();
	this->posicionEnfocadaDelJugador2 = new Posicion();
	list<string>* idContenidos = new list<string>();

	float ancho_fisico = ANCHO_FISICO_PERSONAJE/cant_columnas;
	float alto_fisico = ALTO_FISICO_PERSONAJE/cant_filas;

	if ( this->tipo == "modos" )
	{
		idContenidos->push_back("P1_vs_P2");
		idContenidos->push_back("P1_vs_CPU");
		idContenidos->push_back("Práctica");
		ancho_fisico = ANCHO_FISICO_MODO/cant_columnas;
		alto_fisico = ALTO_FISICO_MODO/cant_filas;

	}
	else if ( this->tipo == "personajes")
	{
		idContenidos->push_back("sub-zero");
		idContenidos->push_back("sonya");
		idContenidos->push_back("sub-zero");
		idContenidos->push_back("sonya");
		idContenidos->push_back("sub-zero");
		idContenidos->push_back("sonya");
		idContenidos->push_back("sub-zero");
		idContenidos->push_back("sonya");
		idContenidos->push_back("sub-zero");
		idContenidos->push_back("sonya");
		idContenidos->push_back("sub-zero");
		idContenidos->push_back("sonya");
	}

	list<string>::iterator itIdContenidos = idContenidos->begin();

	float anchopxDestino_boton = anchopx/cant_columnas;
	float altopxDestino_boton = altopx/cant_filas;

    this->matriz = new Boton**[this->cant_filas];
	for ( int y = 0 ; y < this->cant_filas ; y++ )
	{
		this->matriz[y] = new Boton*[this->cant_columnas];

		for ( int x = 0 ; x < this->cant_columnas ; x++ )
		{
			Posicion* posicionModelo = new Posicion(x,y);

			SDL_Rect rectOrigen;
			rectOrigen.y = y * alto_fisico;
			rectOrigen.x = x * ancho_fisico;
			rectOrigen.w = ancho_fisico;
			rectOrigen.h = alto_fisico;

			SDL_Rect rectDestino;
			rectDestino.y = posicion->getY() + altopxDestino_boton * y;
			rectDestino.x = posicion->getX() + anchopxDestino_boton * x;
			rectDestino.w = anchopxDestino_boton;
			rectDestino.h = altopxDestino_boton;

			this->matriz[y][x] = new Boton(posicionModelo, *(itIdContenidos++), rectOrigen, rectDestino);

		}
	}

	this->idContenidoElegido_paraJugador1 = "";
	this->idContenidoElegido_paraJugador2 = "";
	this->idContenidoEnfocado_paraJugador1 = "";
	this->idContenidoEnfocado_paraJugador2 = "";

	this->gButtonSpriteSheetTexture = new Textura();
	this->gButtonSpriteSheetTexture2 = new Textura();
	this->gButtonSpriteSheetTexture3 = new Textura();

	this->tipoDeControl_jugador1 = tipoDeControl_jugador1;
	this->tipoDeControl_jugador2 = tipoDeControl_jugador2;
	this->modo_juego_elegido = modo_juego_elegido;
	this->controladorBotonera = new ControladorBotonera(this->cant_filas, this->cant_columnas);
	this->elegirPosicionAleatoriamente = true;
	this->esElegidoPersonaje1 = false;
	this->esElegidoPersonaje2 = false;
}

bool Botonera::loadMedia(string path_imagen1, string path_imagen2, string path_imagen3) {
	//Loading success flag
	bool success = true;
	//Load sprites
	if( !this->gButtonSpriteSheetTexture->loadFromFile(path_imagen1) )
	{
		Logger::getInstance()->error("Failed to load button sprite texture 1!");
		success = false;
	}
	if( !this->gButtonSpriteSheetTexture2->loadFromFile(path_imagen2) )
	{
		Logger::getInstance()->error("Failed to load button sprite texture 2!");
		success = false;
	}
	if( !this->gButtonSpriteSheetTexture3->loadFromFile(path_imagen3) )
	{
		Logger::getInstance()->error("Failed to load button sprite texture 3!");
		success = false;
	}

	return success;

}

Botonera::~Botonera() {
	this->gButtonSpriteSheetTexture->free();
	this->gButtonSpriteSheetTexture2->free();
	this->gButtonSpriteSheetTexture3->free();
}

void Botonera::manejarEventoJugador(SDL_Event evento) {

    //Cargo los botones de los joysticks
    TheInputHandlerMenu::Instance()->handleEventsJoysticks(evento);

    if(this->tipoDeControl_jugador1 == "JOYSTICK")
    {
    	if ( !this->esElegidoPersonaje1 )
    		this->controladorBotonera->identificarOrdenJoystick(this->posicionEnfocadaDelJugador1, JOYSTICK1MENU);
    	if( this->modo_juego_elegido == "P1_vs_P2")
    	{
    		if ( !this->esElegidoPersonaje2 )
    			this->controladorBotonera->identificarOrdenJoystick(this->posicionEnfocadaDelJugador2, JOYSTICK2MENU);
    	}

	}
    else
    {
		//Si se presiona una tecla
		if ( evento.key.repeat == 0 )
		{
			if ( !this->esElegidoPersonaje1 )
				this->controladorBotonera->identificarOrdenJugador1(this->posicionEnfocadaDelJugador1);

			if( this->modo_juego_elegido == "P1_vs_P2")
			{
				if ( !this->esElegidoPersonaje2 )
					this->controladorBotonera->identificarOrdenJugador2(this->posicionEnfocadaDelJugador2);
			}
		}
	}

    if( this->modo_juego_elegido != "P1_vs_P2")
    {
		if ( this->elegirPosicionAleatoriamente )
		{
			this->posicionEnfocadaDelJugador2 = this->controladorBotonera->posicionarAleatoriamente();
			this->idContenidoEnfocado_paraJugador2 = matriz[this->posicionEnfocadaDelJugador2->getY()][this->posicionEnfocadaDelJugador2->getX()]->getIdContenido();
			this->elegirPosicionAleatoriamente = false;
		}
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
			Posicion* posActual = matriz[y][x]->getPosicionModelo();

			if ( this->posicionEnfocadaDelJugador1->tieneMismasCoordenadasQue(posActual) )
			{
				if ( this->posicionEnfocadaDelJugador1->estoyElegido() )
				{
					matriz[y][x]->getPosicionModelo()->elegir();
					this->idContenidoElegido_paraJugador1 = matriz[y][x]->getIdContenido();
					this->esElegidoPersonaje1 = true;
				}
				else
				{
					matriz[y][x]->getPosicionModelo()->enfocar();
					matriz[y][x]->getPosicionModelo()->deselegir();
					this->idContenidoElegido_paraJugador1 = "";
					this->idContenidoEnfocado_paraJugador1 = matriz[y][x]->getIdContenido();
					this->esElegidoPersonaje1 = false;
				}
			}
			else
			{
				matriz[y][x]->getPosicionModelo()->desenfocar();
				matriz[y][x]->getPosicionModelo()->deselegir();
			}
		}
	}


	if ( this->tipo=="personajes" )
	{
		for ( int y = 0 ; y < this->cant_filas ; y++ )
		{
			for ( int x = 0 ; x < this->cant_columnas ; x++ )
			{
				Posicion* posActual = matriz[y][x]->getPosicionModelo();

				if ( this->posicionEnfocadaDelJugador2->tieneMismasCoordenadasQue(posActual) )
				{
					if ( this->posicionEnfocadaDelJugador2->estoyElegido() )
					{
						matriz[y][x]->getPosicionModelo()->elegir();
						this->idContenidoElegido_paraJugador2 = matriz[y][x]->getIdContenido();
						this->esElegidoPersonaje2 = true;
					}
					else
					{
						matriz[y][x]->getPosicionModelo()->enfocar();
						matriz[y][x]->getPosicionModelo()->deselegir();
						this->idContenidoElegido_paraJugador2 = "";
						this->idContenidoEnfocado_paraJugador2 = matriz[y][x]->getIdContenido();
						this->esElegidoPersonaje2 = false;
					}
				}
			}
		}
	}
}

int Botonera::getCantFilas() {
	return this->cant_filas;
}

void Botonera::dibujar() {

	for ( int y = 0 ; y < this->cant_filas ; y++ )
	{
		for ( int x = 0 ; x < this->cant_columnas ; x++ )
		{

			if ( matriz[y][x]->getPosicionModelo()->estoyEnfocado() )
			{
				matriz[y][x]->render(this->gButtonSpriteSheetTexture2);
			}
			else
			{
				matriz[y][x]->render(this->gButtonSpriteSheetTexture);
			}

			if ( matriz[y][x]->getPosicionModelo()->estoyElegido() )
			{
				matriz[y][x]->render(this->gButtonSpriteSheetTexture3);
			}
		}
	}

}

void Botonera::setPosicionEnfocadaDelJugador1(Posicion* posicionEnfocadaDelJugador1) {
	this->posicionEnfocadaDelJugador1 = posicionEnfocadaDelJugador1;
}

void Botonera::setPosicionEnfocadaDelJugador2(Posicion* posicionEnfocadaDelJugador2) {
	this->posicionEnfocadaDelJugador2 = posicionEnfocadaDelJugador2;
}

string Botonera::getIdContenidoElegidoParaJugador1(){
	return idContenidoElegido_paraJugador1;
}

string Botonera::getIdContenidoElegidoParaJugador2(){
	return idContenidoElegido_paraJugador2;
}

string Botonera::getIdContenidoEnfocadoParaJugador1() const {
	return idContenidoEnfocado_paraJugador1;
}

string Botonera::getIdContenidoEnfocadoParaJugador2() const {
	return idContenidoEnfocado_paraJugador2;
}

bool Botonera::elModoYaFueElegido() {
	return ( this->idContenidoElegido_paraJugador1 != "" );
}

bool Botonera::seEligioElPersonaje1() {
	return this->idContenidoElegido_paraJugador1 != "";
}

bool Botonera::seEligioElPersonaje2() {
	return this->idContenidoElegido_paraJugador2 != "";
}

void Botonera::manejarEventoMouse(SDL_Event evento) {

	if( evento.type == SDL_MOUSEMOTION || evento.type == SDL_MOUSEBUTTONDOWN )
	{
		if ( !this->esElegidoPersonaje1 )
		{
			int x_mouse, y_mouse;
			SDL_GetMouseState( &x_mouse, &y_mouse );

			for ( int y = 0 ; y < this->cant_filas ; y++ )
			{
				for ( int x = 0 ; x < this->cant_columnas ; x++ )
				{
					SDL_Rect rect = matriz[y][x]->getRectDestino();
					int xi = rect.x;
					int xf = rect.x+rect.w;
					int yi = rect.y;
					int yf = rect.y+rect.h;
					if ( x_mouse>xi && x_mouse<xf && y_mouse>yi && y_mouse<yf )
					{
						this->posicionEnfocadaDelJugador1->setXY(x,y);
						this->posicionEnfocadaDelJugador1->enfocar();
						if ( evento.type == SDL_MOUSEBUTTONDOWN )
							this->posicionEnfocadaDelJugador1->elegir();
					}
				}
			}
		}else
		{
			if ( !this->esElegidoPersonaje2 )
			{
				int x_mouse, y_mouse;
				SDL_GetMouseState( &x_mouse, &y_mouse );

				for ( int y = 0 ; y < this->cant_filas ; y++ )
				{
					for ( int x = 0 ; x < this->cant_columnas ; x++ )
					{
						SDL_Rect rect = matriz[y][x]->getRectDestino();
						int xi = rect.x;
						int xf = rect.x+rect.w;
						int yi = rect.y;
						int yf = rect.y+rect.h;
						if ( x_mouse>xi && x_mouse<xf && y_mouse>yi && y_mouse<yf )
						{
							this->posicionEnfocadaDelJugador2->setXY(x,y);
							this->posicionEnfocadaDelJugador2->enfocar();
							if ( evento.type == SDL_MOUSEBUTTONDOWN )
								this->posicionEnfocadaDelJugador2->elegir();
						}
					}
				}
			}

		}
	}

}
