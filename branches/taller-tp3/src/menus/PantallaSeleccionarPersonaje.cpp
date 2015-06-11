/*
 * PantallaSeleccionarPersonaje.cpp
 *
 *  Created on: 30/5/2015
 *      Author: ariel
 */

#include "PantallaSeleccionarPersonaje.h"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

#include "../utils/Logger.h"
#include "../vista/Renderizador.h"
#include "Boton.h"
#include "Botonera.h"
#include "CajaDeTexto.h"
#include "Posicion.h"

PantallaSeleccionarPersonaje::PantallaSeleccionarPersonaje(string modo_juego_elegido, string tipoDeControl_jugador1, string tipoDeControl_jugador2):
																Pantalla(tipoDeControl_jugador1, tipoDeControl_jugador2) {
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

	int screen_width = 640;
	int screen_height = 480;
	int botonera_filas = 3;
	int botonera_colummas = 4;
	Posicion* pos_botoneraPersonajes = new Posicion(screen_width/2-(BUTTON_WIDTH*botonera_colummas)/2,screen_height/8);
	Botonera* botoneraPersonajes = new Botonera("personajes", botonera_filas,botonera_colummas,pos_botoneraPersonajes,
						getTipoDeControlJugador1(), getTipoDeControlJugador2(), this->modo_juego_elegido);
	botoneraPersonajes->setPosicionEnfocadaDelJugador1(new Posicion(3,1));
	botoneraPersonajes->setPosicionEnfocadaDelJugador2(new Posicion(0,1));

	CajaDeTexto* cajaDeTexto = new CajaDeTexto(5,100,100);

	if( !botoneraPersonajes->loadMedia("RECURSOS/grilla1_eleccion_personajes.jpg", "RECURSOS/grilla2_eleccion_personajes.jpg", "RECURSOS/grilla3_eleccion_personajes.jpg")
		&& !cajaDeTexto->loadMedia() )
	{
		Logger::getInstance()->error("Fallo la carga del archivo imagen");
	}
	else
	{

		//The current input text.
		std::string inputText = "";

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
			bool renderText = false;

			if (SDL_PollEvent(&evento))
			{
				if (evento.type == SDL_QUIT){
					juegoCorriendo = false;
				}
				botoneraPersonajes->manejarEventoJugador(evento);
				botoneraPersonajes->actualizarModelo(&salirEleccionPersonajes);
			    renderText = cajaDeTexto->manejarEvento(&inputText, evento);
			}

			botoneraPersonajes->dibujar();
			//TODO corregir error en la llamada de TTF_RenderText_Solid en Textura, que hace que al escribir el primer caracter, piche!
			//cajaDeTexto->dibujar(renderText, inputText);

	        frameTime = SDL_GetTicks() - frameStart;

	        if (frameTime < DELAY_TIME)
	            SDL_Delay((int)(DELAY_TIME - frameTime));
		}

		//Disable text input
		SDL_StopTextInput();

		this->IdPersonaje1Elegido = botoneraPersonajes->getIdContenidoElegidoParaJugador1();
		this->IdPersonaje2Elegido = botoneraPersonajes->getIdContenidoElegidoParaJugador2();
	}

	delete botoneraPersonajes;
	delete cajaDeTexto;
}

string PantallaSeleccionarPersonaje::getIdPersonaje1Elegido() {
	return this->IdPersonaje1Elegido;
}

string PantallaSeleccionarPersonaje::getIdPersonaje2Elegido() {
	return this->IdPersonaje2Elegido;
}

string PantallaSeleccionarPersonaje::getModoJuegoElegido() const {
	return modo_juego_elegido;
}
