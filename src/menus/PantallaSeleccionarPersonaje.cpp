/*
 * PantallaSeleccionarPersonaje.cpp
 *
 *  Created on: 30/5/2015
 *      Author: ariel
 */

#include "PantallaSeleccionarPersonaje.h"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

#include "../utils/Logger.h"
#include "../vista/Renderizador.h"
#include "Boton.h"
#include "Botonera.h"
#include "CajaDeTexto.h"
#include "Posicion.h"

PantallaSeleccionarPersonaje::PantallaSeleccionarPersonaje(int anchopx, int altopx, string modo_juego_elegido, string tipoDeControl_jugador1,
														   string tipoDeControl_jugador2):
														   Pantalla(anchopx, altopx, tipoDeControl_jugador1, tipoDeControl_jugador2) {
	this->modo_juego_elegido = modo_juego_elegido;
}

PantallaSeleccionarPersonaje::~PantallaSeleccionarPersonaje() {
	// TODO Auto-generated destructor stub
}

void PantallaSeleccionarPersonaje::iniciar() {

	//cambio el titulo a pantalla
	string titulo = "Eleccion de Personajes( Modo: ";
	titulo.append(this->modo_juego_elegido);
	titulo.append(" ).");
	SDL_SetWindowTitle( Renderizador::Instance()->getWindow(), titulo.c_str() );

	bool juegoCorriendo = true;
	int botonera_filas = 3;
	int botonera_colummas = 4;

	Posicion* pos_botoneraPersonajes = new Posicion(this->getAnchopx()/2-(BUTTON_WIDTH*botonera_colummas)/2, 20);
	Botonera* botoneraPersonajes = new Botonera("personajes", botonera_filas,botonera_colummas,pos_botoneraPersonajes,
						getTipoDeControlJugador1(), getTipoDeControlJugador2(), this->modo_juego_elegido);

	botoneraPersonajes->setPosicionEnfocadaDelJugador1(new Posicion(3,1));
	botoneraPersonajes->setPosicionEnfocadaDelJugador2(new Posicion(0,1));

	int cant_letras = 9;

	SDL_Color textColor1 = { 0xFF, 0, 0, 0xFF };
	int posX_1 = 10;
	int posY_1 = this->getAltopx() - 50;
	CajaDeTexto* cajaDeTextoPersonaje1 = new CajaDeTexto(cant_letras,textColor1,posX_1,posY_1);

	SDL_Color textColor2 = { 0, 0xFF, 0, 0xFF };
	int posX_2 = this->getAnchopx() - 140;
	int posY_2 = this->getAltopx() - 50;
	CajaDeTexto* cajaDeTextoPersonaje2 = new CajaDeTexto(cant_letras,textColor2,posX_2,posY_2);

	bool loadMedia_botonera = botoneraPersonajes->loadMedia("RECURSOS/grilla1_eleccion_personajes.jpg",
															"RECURSOS/grilla2_eleccion_personajes.jpg",
															"RECURSOS/grilla3_eleccion_personajes.jpg");

	bool loadMedia_cajaDeTextoPersonaje1 = cajaDeTextoPersonaje1->loadMedia();
	bool loadMedia_cajaDeTextoPersonaje2 = cajaDeTextoPersonaje2->loadMedia();

	if( loadMedia_botonera && loadMedia_cajaDeTextoPersonaje1 && loadMedia_cajaDeTextoPersonaje2 )
	{
		//Enable text input
		SDL_StartTextInput();

		bool salirEleccionPersonajes = false;

	    static const int FPS = 60;
	    static const int DELAY_TIME = 1000.0f / FPS;
	    Uint32 frameStart, frameTime;

	    while( !salirEleccionPersonajes && juegoCorriendo )
		{
			frameStart = SDL_GetTicks();
			SDL_Event evento;

			//The rerender text flag
			bool renderText1 = false;
			bool renderText2 = false;

			if (SDL_PollEvent(&evento))
			{
				if (evento.type == SDL_QUIT){
					juegoCorriendo = false;
				}

				//para salir del juego con la tecla ESC
			    if( evento.type == SDL_KEYUP && evento.key.repeat == 0 ){
			        if (evento.key.keysym.sym == SDLK_ESCAPE){
			            juegoCorriendo = false;
			        }
			    }

				botoneraPersonajes->manejarEventoJugador(evento);
				botoneraPersonajes->actualizarModelo(&salirEleccionPersonajes);
			    renderText1 = cajaDeTextoPersonaje1->manejarEvento(evento);
			    renderText2 = cajaDeTextoPersonaje2->manejarEvento(evento);
			}

			// CLEAR screen
			SDL_SetRenderDrawColor( Renderizador::Instance()->getRenderer(), 0x0F, 0x00, 0x00, 0xFF );
			SDL_RenderClear( Renderizador::Instance()->getRenderer() );
			// DIBUJAR
			botoneraPersonajes->dibujar();
			cajaDeTextoPersonaje1->dibujar(renderText1);
			cajaDeTextoPersonaje2->dibujar(renderText2);
			// UPDATE screen
			SDL_RenderPresent( Renderizador::Instance()->getRenderer() );

	        frameTime = SDL_GetTicks() - frameStart;

	        if (frameTime < DELAY_TIME)
	            SDL_Delay((int)(DELAY_TIME - frameTime));
		}

		//Disable text input
		SDL_StopTextInput();

		this->IdPersonaje1Elegido = botoneraPersonajes->getIdContenidoElegidoParaJugador1();
		this->IdPersonaje2Elegido = botoneraPersonajes->getIdContenidoElegidoParaJugador2();
		this->nombrePersonaje1 = cajaDeTextoPersonaje1->getTexto();
		this->nombrePersonaje1 = cajaDeTextoPersonaje1->getTexto();

	}else {
		if ( !loadMedia_botonera )
			Logger::getInstance()->error("No se pudo cargar imagenes para la botonera en la pantalla de eleccion de personajes");
		if ( !loadMedia_cajaDeTextoPersonaje1 )
			Logger::getInstance()->error("No se pudo cargar imagenes para la caja de texto del personaje 1 en la pantalla de eleccion de personajes");
		if ( !loadMedia_cajaDeTextoPersonaje2 )
			Logger::getInstance()->error("No se pudo cargar imagenes para la caja de texto del personaje 2 en la pantalla de eleccion de personajes");
	}

	delete botoneraPersonajes;
	delete cajaDeTextoPersonaje1;
	delete cajaDeTextoPersonaje2;
}

string PantallaSeleccionarPersonaje::getIdPersonaje1Elegido() {
	return this->IdPersonaje1Elegido;
}

string PantallaSeleccionarPersonaje::getIdPersonaje2Elegido() {
	return this->IdPersonaje2Elegido;
}

string PantallaSeleccionarPersonaje::getNombrePersonaje1() const {
	return nombrePersonaje1;
}

string PantallaSeleccionarPersonaje::getNombrePersonaje2() const {
	return nombrePersonaje2;
}

string PantallaSeleccionarPersonaje::getModoJuegoElegido() const {
	return modo_juego_elegido;
}
