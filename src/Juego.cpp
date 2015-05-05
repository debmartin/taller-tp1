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

using std::pair;

Juego::Juego(pair<Personaje*, PersonajeDibujable*>& personaje1, pair<Personaje*, PersonajeDibujable*>& personaje2) :
    jugador1(personaje1.first), jugador2(personaje2.first), jugadorDibujable1(personaje1.second), jugadorDibujable2(personaje2.second){
	juegoCorriendo = true;

	agregarObservadoresJugador(jugador1, jugadorDibujable1);
	agregarObservadoresJugador(jugador2, jugadorDibujable2);

	controladorPersonaje = new ControladorPersonaje(jugador1, jugador2);
	hud = new HUD(Renderizador::Instance()->getWindow(), "Sonia", "Sub-zero");
	//hud->disminuirEnergia1(23);
	//hud->disminuirEnergia2(130);
	jugador1->agregarObservador(hud);
	jugador2->agregarObservador(hud);
}

void Juego::agregarObservadoresJugador(Personaje* unPersonaje,
		PersonajeDibujable* unPersonajeDibujable) {
	//Agrego observadores del Personaje.
	unPersonaje->agregarObservador(unPersonajeDibujable);
	unPersonaje->agregarObservador(VentanaGrafica::Instance());
}

void Juego::render()
{

	VentanaGrafica::Instance()->dibujarTodo();
	hud->dibujar();
	SDL_RenderPresent(Renderizador::Instance()->getRenderer());

}

void Juego::update()
{
	// INICIO CODIGO USUARIO
	this->jugador1->update(jugador2->getPosicion());
	this->jugador2->update(jugador1->getPosicion());
	this->actualizarOrientacionJugadores();

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

void Juego::actualizarOrientacionJugadores() {

	if ( jugadorDibujable1->getPosicionX() > jugadorDibujable2->getPosicionX() )
	{
		jugadorDibujable1->cambiarOrientacionHaciaIzquierda();
		jugadorDibujable2->cambiarOrientacionHaciaDerecha();
	}
	else
	{
		jugadorDibujable1->cambiarOrientacionHaciaDerecha();
		jugadorDibujable2->cambiarOrientacionHaciaIzquierda();
	}
}

Juego::~Juego(){
//    delete VentanaGrafica::Instance();
//    delete jugadorDibujable1;
//    delete jugador1;
//    delete escenarioG;
}
