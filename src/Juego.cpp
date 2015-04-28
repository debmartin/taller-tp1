/*
 * Juego.cpp
 *
 *  Created on: 27/3/2015
 *      Author: val
 */

#include "Juego.h"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>

#include "controlador/ControladorPersonaje.h"
#include "modelo/Personaje.h"
#include "utils/Logger.h"
#include "vista/PersonajeDibujable.h"
#include "vista/VentanaGrafica.h"

#define TEXTO_ERROR_TEXTURA "ERROR AL CREAR TEXTURA"

Juego::Juego()
{
	juegoCorriendo = true;
	jugador1 = new Personaje();
	jugador2 = new Personaje();
	jugadorDibujable1 = new PersonajeDibujable();
	jugadorDibujable2 = new PersonajeDibujable();
	controladorPersonaje = new ControladorPersonaje();

}

void Juego::agregarJugador1(Personaje* unPersonaje,
		PersonajeDibujable* unPersonajeDibujable) {

	this->jugador1 = unPersonaje;
	this->jugadorDibujable1 = unPersonajeDibujable;

	//Agrego observadores del Personaje.
	this->jugador1->agregarObservador(jugadorDibujable1);
	this->jugador1->agregarObservador(VentanaGrafica::Instance());

	controladorPersonaje->agregarPersonaje1(this->jugador1);
}

void Juego::agregarJugador2(Personaje* unPersonaje,
		PersonajeDibujable* unPersonajeDibujable) {

	this->jugador2 = unPersonaje;
	this->jugadorDibujable2 = unPersonajeDibujable;

	//Agrego observadores del Personaje.
	this->jugador2->agregarObservador(jugadorDibujable2);
	this->jugador2->agregarObservador(VentanaGrafica::Instance());

	controladorPersonaje->agregarPersonaje2(this->jugador2);
	this->jugador1->agregarOponente(this->jugador2);
	this->jugador2->agregarOponente(this->jugador1);
}

void Juego::render()
{
	VentanaGrafica::Instance()->dibujarTodo();
}

void Juego::update()
{
	// INICIO CODIGO USUARIO
	this->jugador1->update();
	this->jugador2->update();

	VentanaGrafica::Instance()->actualizar();
	// FIN CODIGO USUARIO
}

void Juego::handleEvents(bool& recargar)
{
	SDL_Event evento;
	// INICIO CODIGO USUARIO
	if (SDL_PollEvent(&evento))
	{
		//para salir del juego con la tecla ESC
	    if( evento.type == SDL_KEYUP && evento.key.repeat == 0 ){
	        if (evento.key.keysym.sym == SDLK_ESCAPE){
	            juegoCorriendo = false;
	        }
	    }

	    //la tecla r para recargar el juego inicial
	    if( evento.type == SDL_KEYUP && evento.key.repeat == 0 ){
	        if (evento.key.keysym.sym == SDLK_r){
	            Logger::getInstance()->info("Se presiona: Tecla R. Se recarga el juego.");
	            juegoCorriendo = false;
	            recargar = true;
	        }
	    }

		if (evento.type == SDL_QUIT){
			juegoCorriendo = false;
		} else if (! controladorPersonaje->manejar_Evento(evento)){
			juegoCorriendo = false;
		}

	} else {
	        controladorPersonaje->continuarAccionPreviaPersonaje1();
	        controladorPersonaje->continuarAccionPreviaPersonaje2();
	}
}

bool Juego::running() { return juegoCorriendo; }

Juego::~Juego(){
//    delete VentanaGrafica::Instance();
//    delete jugadorDibujable1;
//    delete jugador1;
//    delete escenarioG;
}
