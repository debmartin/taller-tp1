/*
 * Juego.cpp
 *
 *  Created on: 27/3/2015
 *      Author: val
 */

#include "Juego.h"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <string>
#include <utility>

#include "controlador/ControladorPersonaje.h"
#include "modelo/Jugador.h"
#include "modelo/Personaje.h"
#include "modelo/Vector2f.h"
#include "utils/Logger.h"
#include "vista/EscenarioGrafico.h"
#include "vista/hud/HUD.h"
#include "vista/PersonajeDibujable.h"
#include "vista/Renderizador.h"
#include "vista/VentanaGrafica.h"

#define TEXTO_ERROR_TEXTURA "ERROR AL CREAR TEXTURA"

using std::pair;

Juego::Juego(Jugador* jugador1, Jugador* jugador2){
	juegoCorriendo = true;
	this->jugador1 = jugador1;
	this->jugador2 = jugador2;

	agregarObservadoresJugador(jugador1);
	agregarObservadoresJugador(jugador2);

	//Se pueden distingir los tipos de controles para cada jugador
	string tipoDeControl_jugador1 = jugador1->getTipoControl();
	string tipoDeControl_jugador2 = jugador2->getTipoControl();

	controladorPersonaje = new ControladorPersonaje(jugador1, jugador2, tipoDeControl_jugador1);
	hud = new HUD(Renderizador::Instance()->getWindow(), jugador2->getPersonaje()->getId(), jugador1->getPersonaje()->getId());
	//hud->disminuirEnergia1(23);
	//hud->disminuirEnergia2(130);
	jugador1->getPersonaje()->agregarObservador(hud);
	jugador2->getPersonaje()->agregarObservador(hud);

	this->posicionarPersonajes_enEjeX();
}

void Juego::agregarObservadoresJugador(Jugador* unJugador) {
	//Agrego observadores del Personaje.
	unJugador->getPersonaje()->agregarObservador(unJugador->getPersonajeDibujable());
	unJugador->getPersonaje()->agregarObservador(VentanaGrafica::Instance());
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
	this->jugador1->getPersonaje()->update(jugador2->getPersonaje());
	this->jugador2->getPersonaje()->update(jugador1->getPersonaje());
	this->actualizarOrientacionJugadores();

	VentanaGrafica::Instance()->actualizar();
	// FIN CODIGO USUARIO

	if (jugador1->getPersonaje()->estaMuerto()) {
//        juegoCorriendo = false;
        Logger::getInstance()->info("GAME OVER JUGADOR 1");
    }
	if (jugador2->getPersonaje()->estaMuerto()) {
//        juegoCorriendo = false;
        Logger::getInstance()->info("GAME OVER JUGADOR 2");
    }
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

	if ( jugador1->getPersonaje()->getPosicion().X() > jugador2->getPersonaje()->getPosicion().X() )
	{
		jugador1->getPersonajeDibujable()->cambiarOrientacionHaciaIzquierda();
		jugador2->getPersonajeDibujable()->cambiarOrientacionHaciaDerecha();

		jugador1->getPersonaje()->orientar(DIRECCION_IZQUIERDA);
		jugador2->getPersonaje()->orientar(DIRECCION_DERECHA);

		jugador1->getPersonaje()->espejarBVH();
	}
	else
	{
		jugador1->getPersonajeDibujable()->cambiarOrientacionHaciaDerecha();
		jugador2->getPersonajeDibujable()->cambiarOrientacionHaciaIzquierda();

		jugador1->getPersonaje()->orientar(DIRECCION_DERECHA);
		jugador2->getPersonaje()->orientar(DIRECCION_IZQUIERDA);

		jugador2->getPersonaje()->espejarBVH();
	}
}

Juego::~Juego(){
//    delete VentanaGrafica::Instance();
//    delete jugadorDibujable1;
//    delete jugador1;
//    delete escenarioG;
}

void Juego::posicionarPersonajes_enEjeX()
{
	double anchoEscenario = VentanaGrafica::Instance()->getEscenario()->getAnchoLogico();
	double anchoVentana = VentanaGrafica::Instance()->getAnchoLogico();

	jugador1->posicionarPersonaje_enEjeX(anchoEscenario/2+anchoVentana/3);
	jugador1->posicionarPersonaje_enEjeX(anchoEscenario/2);//+anchoVentana/3);
	jugador2->posicionarPersonaje_enEjeX(anchoEscenario/2-anchoVentana/3);
}
