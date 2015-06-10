/*
 * Botonera.cpp
 *
 *  Created on: 16/5/2015
 *      Author: ariel
 */

#include "Botonera.h"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <iostream>
#include <list>
#include <map>

#include "../utils/Logger.h"
#include "../vista/Renderizador.h"
#include "Boton.h"
#include "Posicion.h"
#include "Textura.h"

Botonera::Botonera(string tipo, int cant_filas, int cant_columnas, Posicion* posicion,
					string tipoDeControl_jugador1, string tipoDeControl_jugador2,
					string modo_juego_elegido) {

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

			SDL_Rect rect;
			rect.y = y * 127;
			rect.x = x * 127;
			if ( this->tipo == "personajes")
				rect.x = x * 118.2;

			rect.w = BUTTON_WIDTH;
			rect.h = BUTTON_HEIGHT;
			boton->cargarDimension(rect);

			this->matriz[y][x] = boton;

		}
	}

	this->gButtonSpriteSheetTexture = new Textura();
	this->gButtonSpriteSheetTexture2 = new Textura();
	this->gButtonSpriteSheetTexture3 = new Textura();

	this->tipoDeControl_jugador1 = tipoDeControl_jugador1;
	this->tipoDeControl_jugador2 = tipoDeControl_jugador2;
	this->modo_juego_elegido = modo_juego_elegido;

	ControladorJoystick::Instance()->initialiseJoysticks();
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
    TheInputHandler::Instance()->handleEventsJoysticks(evento);

    if(this->tipoDeControl_jugador1 == "JOYSTICK"){
    	identificarOrdenJoystickPersonaje(JOYSTICK1);
    	if( this->modo_juego_elegido == "P1_vs_P2"){
    		identificarOrdenJoystickPersonaje(JOYSTICK2);
    	}
	}else{
		//Si se presiona una tecla
		if ( evento.key.repeat == 0 )
		{
			identificarOrdenPersonaje1();
			/* TODO descomentar cuando se implemente la forma de elegirse aleatoriamente
			 * el personaje 2 cuando se juega con la CPU o es en modo practica
			 */
			//if( this->modo_juego_elegido == "P1_vs_P2")
			//{
				identificarOrdenPersonaje2();
			//}
		}
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

void Botonera::identificarOrdenPersonaje1() {

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

void Botonera::identificarOrdenPersonaje2() {

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
	else if (estadoTeclado[SDL_SCANCODE_SPACE])
	{
		this->posicionEnfocadaDelJugador2->elegir();
	}
}

void Botonera::identificarOrdenJoystickPersonaje(JoyNumber numeroJoystick) {

	std::map<string, bool>* estadoJoy = TheInputHandler::Instance()->getJoystickState(numeroJoystick);

	if ( (*estadoJoy)["JOY_IZQUIERDA"] ){
		Logger::getInstance()->error("Se presiona: Tecla izquierda.");

	}else if ( (*estadoJoy)["JOY_DERECHA"] ){
		Logger::getInstance()->error("Se presiona: Tecla derecha.");

	}else if ( (*estadoJoy)["JOY_ARRIBA"] ){
		Logger::getInstance()->error("Se presiona: Tecla arriba.");

	}else if ( (*estadoJoy)["JOY_ABAJO"] ){
		Logger::getInstance()->error("Se presiona: Tecla abajo.");

	}else if((*estadoJoy)["JOY_PINIA_ALTA"]){
		Logger::getInstance()->error("Se presiona: Seleccion opcion.");
	}

}
