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

Juego::Juego(EscenarioGrafico* escenario, Personaje* personaje, PersonajeDibujable* personajeDib) :
    escenarioG(escenario), jugador1(personaje), jugadorDibujable1(personajeDib){

	juegoCorriendo = true;

	//Agrego observadores del Personaje.
	personaje->agregarObservador(personajeDib);
	personaje->agregarObservador(VentanaGrafica::Instance());

	this->controladorJuego = new Controlador(this->jugador1);
}

void Juego::render()
{
	VentanaGrafica::Instance()->dibujarTodo();
}

void Juego::update()
{
	// INICIO CODIGO USUARIO
	this->jugador1->update();
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
	}
}

// a function to access the private running variable
bool Juego::running() { return juegoCorriendo; }

Juego::~Juego(){
    delete controladorJuego;
//    delete VentanaGrafica::Instance();
//    delete jugadorDibujable1;
//    delete jugador1;
//    delete escenarioG;
}


