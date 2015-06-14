/*
 * PantallaSeleccionarModo.cpp
 *
 *  Created on: 30/5/2015
 *      Author: ariel
 */

#include "PantallaSeleccionarModo.h"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

#include "../utils/Logger.h"
#include "../vista/Renderizador.h"
#include "Boton.h"
#include "Botonera.h"
#include "Posicion.h"

PantallaSeleccionarModo::PantallaSeleccionarModo(int anchopx, int altopx, string tipoDeControl_jugador1,
												 string tipoDeControl_jugador2):
												 Pantalla(anchopx, altopx, tipoDeControl_jugador1, tipoDeControl_jugador2) {
}

PantallaSeleccionarModo::~PantallaSeleccionarModo() {
	delete this->botonera; this->botonera = NULL;
}

void PantallaSeleccionarModo::iniciar() {

	//cambio el titulo a pantalla
	SDL_SetWindowTitle( Renderizador::Instance()->getWindow(), "Eleccion de Modo" );

	bool juegoCorriendo = true;

	Posicion* pos_modosDeJuego = new Posicion(this->getAnchopx()/2-BUTTON_WIDTH/2, this->getAltopx()/8);
	botonera = new Botonera("modos",3,1,pos_modosDeJuego, getTipoDeControlJugador1(), getTipoDeControlJugador2());
	botonera->setPosicionEnfocadaDelJugador1(new Posicion(0,0));

	if( !botonera->loadMedia("RECURSOS/grilla1_eleccion_modo.jpg", "RECURSOS/grilla2_eleccion_modo.jpg", "RECURSOS/grilla3_eleccion_modo.jpg") )
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

				botonera->manejarEventoJugador(evento);
				botonera->actualizarModelo();
				if ( botonera->elModoYaFueElegido() )
				{
					salirMenuModosDeJuego = true;
				}
			}

			// CLEAR screen
			SDL_SetRenderDrawColor( Renderizador::Instance()->getRenderer(), 0x0F, 0x00, 0x00, 0xFF );
			SDL_RenderClear( Renderizador::Instance()->getRenderer() );
			// DIBUJA
			botonera->dibujar();
			// UPDATE screen
			SDL_RenderPresent( Renderizador::Instance()->getRenderer() );

			frameTime = SDL_GetTicks() - frameStart;

			if (frameTime < DELAY_TIME)
				SDL_Delay((int)(DELAY_TIME - frameTime));
		}

		modo_juego_elegido = botonera->getIdContenidoElegidoParaJugador1();
	}

}

string PantallaSeleccionarModo::getModoDeJuegoElegido() {
	return this->modo_juego_elegido;
}
