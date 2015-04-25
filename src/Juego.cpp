/*
 * Juego.cpp
 *
 *  Created on: 27/3/2015
 *      Author: val
 */

#include "Juego.h"
#include <cstddef>
#include <SDL2/SDL.h> //TODO: Solo para tests

#include "vista/VentanaGrafica.h"
#include "vista/Sprite.h"

#define TEXTO_ERROR_TEXTURA "ERROR AL CREAR TEXTURA"

Juego::Juego()
{
	juegoCorriendo = true;
	controladorJuego = new Controlador();
	jugador1 = new Personaje();
	jugador2 = new Personaje();
	jugadorDibujable1 = new PersonajeDibujable();
	jugadorDibujable2 = new PersonajeDibujable();

}

void Juego::agregarJugador1(Personaje* unPersonaje,
		PersonajeDibujable* unPersonajeDibujable) {

	this->jugador1 = unPersonaje;
	this->jugadorDibujable1 = unPersonajeDibujable;

	//Agrego observadores del Personaje.
	this->jugador1->agregarObservador(jugadorDibujable1);
	this->jugador1->agregarObservador(VentanaGrafica::Instance());

	this->controladorJuego = new Controlador(this->jugador1);
}

void Juego::agregarJugador2(Personaje* unPersonaje,
		PersonajeDibujable* unPersonajeDibujable) {

	this->jugador2 = unPersonaje;
	this->jugadorDibujable2 = unPersonajeDibujable;

	//Agrego observadores del Personaje.
	this->jugador2->agregarObservador(jugadorDibujable2);
	this->jugador2->agregarObservador(VentanaGrafica::Instance());

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
		if (evento.type == SDL_QUIT){
			juegoCorriendo = false;
		} else if (! controladorJuego->manejar_Evento(evento)){
			juegoCorriendo = false;
			recargar = true;
		}
	} else {
	        controladorJuego->continuarAccionPrevia();
	}
}

bool Juego::running() { return juegoCorriendo; }

Juego::~Juego(){
    delete controladorJuego;
//    delete VentanaGrafica::Instance();
//    delete jugadorDibujable1;
//    delete jugador1;
//    delete escenarioG;
}
