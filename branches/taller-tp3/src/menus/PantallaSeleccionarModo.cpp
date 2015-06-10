/*
 * PantallaSeleccionarModo.cpp
 *
 *  Created on: 30/5/2015
 *      Author: ariel
 */

#include "PantallaSeleccionarModo.h"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

#include "../utils/Logger.h"
#include "../vista/Renderizador.h"
#include "Boton.h"
#include "Botonera.h"
#include "Posicion.h"

PantallaSeleccionarModo::PantallaSeleccionarModo(string tipoDeControl_jugador1,
		string tipoDeControl_jugador2):Pantalla(tipoDeControl_jugador1, tipoDeControl_jugador2) {
}

PantallaSeleccionarModo::~PantallaSeleccionarModo() {

}

void PantallaSeleccionarModo::iniciar() {

	//cambio el titulo a pantalla
	SDL_SetWindowTitle( Renderizador::Instance()->getWindow(), "Eleccion de Modo" );

	bool juegoCorriendo = true;

	int screen_width = 640;
	int screen_height = 480;
	Posicion* pos_modosDeJuego = new Posicion(screen_width/2-BUTTON_WIDTH/2, screen_height/8);
	Botonera* botoneraModosDeJuego = new Botonera("modos",3,1,pos_modosDeJuego, getTipoDeControlJugador1(), getTipoDeControlJugador2());
	botoneraModosDeJuego->setPosicionEnfocadaDelJugador1(new Posicion(0,0));

	if( !botoneraModosDeJuego->loadMedia("RECURSOS/grilla1_eleccion_modo.jpg", "RECURSOS/grilla2_eleccion_modo.jpg", "RECURSOS/grilla3_eleccion_modo.jpg") )
	{
		Logger::getInstance()->error("Fallo la carga los archivos imagenes");
	}
	else
	{
		bool salirMenuModosDeJuego = false;

		static const int FPS = 60;
		static const int DELAY_TIME = 1000.0f / FPS;
		Uint32 frameStart, frameTime;

		while( !salirMenuModosDeJuego && juegoCorriendo )
		{
			frameStart = SDL_GetTicks();
			SDL_Event evento;

			if (SDL_PollEvent(&evento))
			{
				if (evento.type == SDL_QUIT){
					juegoCorriendo = false;
				}

				botoneraModosDeJuego->manejarEventoJugador(evento);
				botoneraModosDeJuego->actualizarModelo(&salirMenuModosDeJuego);
			}

			botoneraModosDeJuego->dibujar();

			frameTime = SDL_GetTicks() - frameStart;

			if (frameTime < DELAY_TIME)
				SDL_Delay((int)(DELAY_TIME - frameTime));
		}

		modo_juego_elegido = botoneraModosDeJuego->getIdContenidoElegidoParaJugador1();
	}

	delete botoneraModosDeJuego;

}

string PantallaSeleccionarModo::getModoDeJuegoElegido() {
	return this->modo_juego_elegido;
}
