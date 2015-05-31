/*
 * PantallaSeleccionarPersonaje.cpp
 *
 *  Created on: 30/5/2015
 *      Author: ariel
 */

#include "PantallaSeleccionarPersonaje.h"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

#include "../utils/Logger.h"
#include "../vista/Renderizador.h"
#include "Boton.h"
#include "Botonera.h"
#include "Posicion.h"

PantallaSeleccionarPersonaje::PantallaSeleccionarPersonaje(string modo_juego_elegido) {
	this->modo_juego_elegido = modo_juego_elegido;
}

PantallaSeleccionarPersonaje::~PantallaSeleccionarPersonaje() {
	// TODO Auto-generated destructor stub
}

void PantallaSeleccionarPersonaje::iniciar() {

	this->IdPersonaje1Elegido = "sub-zero";
	this->IdPersonaje2Elegido = "sonya";

	//TODO falta sincronizar con el renderizador que ya esta iniciado

	//cambio el titulo a pantalla
	SDL_SetWindowTitle( Renderizador::Instance()->getWindow(), "Eleccion de Personajes" );

	bool juegoCorriendo = true;

	int screen_width = 640;
	int screen_height = 480;
	int botonera_filas = 3;
	int botonera_colummas = 4;
	Posicion* pos_botoneraPersonajes = new Posicion(screen_width/2-(BUTTON_WIDTH*botonera_colummas)/2,screen_height/8);
	Posicion* posIni_enfocadoPersonajes = new Posicion(3,1);
	Botonera* botoneraPersonajes = new Botonera(botonera_filas,botonera_colummas,pos_botoneraPersonajes, posIni_enfocadoPersonajes);

	if( !botoneraPersonajes->loadMedia("RECURSOS/grilla_eleccion_personajes.jpg") )
	{
		Logger::getInstance()->error("Fallo la carga del archivo imagen");
	}
	else
	{
		bool salirEleccionPersonajes = false;

	    static const int FPS = 60;
	    static const int DELAY_TIME = 1000.0f / FPS;
	    Uint32 frameStart, frameTime;

	    while( !salirEleccionPersonajes && juegoCorriendo )
		{
			frameStart = SDL_GetTicks();
			// INICIO CODIGO USUARIO
			//manejo el evento
			SDL_Event evento;

			if (SDL_PollEvent(&evento))
			{
				//para salir del juego con la tecla ESC
				if( evento.type == SDL_KEYUP && evento.key.repeat == 0 ){
					if (evento.key.keysym.sym == SDLK_ESCAPE){
						salirEleccionPersonajes = true;
					}
				}

				if (evento.type == SDL_QUIT){
					juegoCorriendo = false;
				}

				//Si se presiona una tecla
				if ( evento.key.repeat == 0 ){
					botoneraPersonajes->manejarEvento(evento);
				}

				botoneraPersonajes->actualizarModelo();

			}

			botoneraPersonajes->dibujar();

	        frameTime = SDL_GetTicks() - frameStart;

	        if (frameTime < DELAY_TIME)
	            SDL_Delay((int)(DELAY_TIME - frameTime));
		}
	}

	delete botoneraPersonajes;


}

string PantallaSeleccionarPersonaje::getIdPersonaje1Elegido() {
	return this->IdPersonaje1Elegido;
}

string PantallaSeleccionarPersonaje::getIdPersonaje2Elegido() {
	return this->IdPersonaje2Elegido;
}