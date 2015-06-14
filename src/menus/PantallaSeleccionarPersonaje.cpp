/*
 * PantallaSeleccionarPersonaje.cpp
 *
 *  Created on: 30/5/2015
 *      Author: ariel
 */

#include "PantallaSeleccionarPersonaje.h"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <utility>

#include "../controlador/ControladorJoystickMenu.h"
#include "../modelo/estado/Estado.h"
#include "../modelo/Vector2f.h"
#include "../utils/Logger.h"
#include "../vista/Renderizador.h"
#include "Boton.h"
#include "Botonera.h"
#include "CajaDeTexto.h"
#include "Posicion.h"

PantallaSeleccionarPersonaje::PantallaSeleccionarPersonaje(int anchopx, int altopx, string modo_juego_elegido, string tipoDeControl_jugador1,
														   string tipoDeControl_jugador2, map<string, PersonajeDibujable*>* personajesDibujables):
														   Pantalla(anchopx, altopx, tipoDeControl_jugador1, tipoDeControl_jugador2) {
	this->modo_juego_elegido = modo_juego_elegido;
	this->personajesDibujables = personajesDibujables;
	this->cajaDeTextoPersonaje1 = new CajaDeTexto();
	this->cajaDeTextoPersonaje2 = new CajaDeTexto();
	this->setearNombrePersonaje1 = true;
	this->setearNombrePersonaje2 = true;
}

PantallaSeleccionarPersonaje::~PantallaSeleccionarPersonaje() {
	delete this->botonera; this->botonera = NULL;
	delete this->cajaDeTextoPersonaje1; this->cajaDeTextoPersonaje1 = NULL;
	delete this->cajaDeTextoPersonaje2; this->cajaDeTextoPersonaje2 = NULL;
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

	int ancho_botonera = BUTTON_WIDTH*botonera_colummas;
	int alto_botonera = BUTTON_HEIGHT*botonera_filas;
	int posX_botonera = this->getAnchopx()/2 - ancho_botonera/2;
	int posY_botonera = this->getAltopx()/10;
	Posicion* pos_botoneraPersonajes = new Posicion(posX_botonera, posY_botonera);
	this->botonera = new Botonera("personajes", botonera_filas,botonera_colummas,pos_botoneraPersonajes,
						getTipoDeControlJugador1(), getTipoDeControlJugador2(), this->modo_juego_elegido);

	this->botonera->setPosicionEnfocadaDelJugador1(new Posicion(3,1));
	this->botonera->setPosicionEnfocadaDelJugador2(new Posicion(0,1));

	int cant_letras = 9;

	int posX_1 = posX_botonera + ancho_botonera + 15;
	int posY_1 = posY_botonera + alto_botonera;
	this->cajaDeTextoPersonaje1 = new CajaDeTexto(cant_letras,posX_1,posY_1);

	int posX_2 = 10;
	int posY_2 = posY_botonera + alto_botonera;
	this->cajaDeTextoPersonaje2 = new CajaDeTexto(cant_letras,posX_2,posY_2);

	bool loadMedia_botonera = this->botonera->loadMedia("RECURSOS/grilla1_eleccion_personajes.jpg",
															"RECURSOS/grilla2_eleccion_personajes.jpg",
															"RECURSOS/grilla3_eleccion_personajes.jpg");

	bool loadMedia_cajaDeTextoPersonaje1 = this->cajaDeTextoPersonaje1->loadMedia();
	bool loadMedia_cajaDeTextoPersonaje2 = this->cajaDeTextoPersonaje2->loadMedia();

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

				this->botonera->manejarEventoJugador(evento);
				this->botonera->actualizarModelo();

				this->manejarEventoNombreDelPersonaje1(evento, &renderText1);
				this->manejarEventoNombreDelPersonaje2(evento, &renderText2);

				if ( this->botonera->seEligioElPersonaje1() && this->botonera->seEligioElPersonaje2() )
				{
					salirEleccionPersonajes = this->iniciarSalida();
				}
			}

			// CLEAR screen
			SDL_SetRenderDrawColor( Renderizador::Instance()->getRenderer(), 0x0F, 0x00, 0x00, 0xFF );
			SDL_RenderClear( Renderizador::Instance()->getRenderer() );

			// DIBUJAR
			this->botonera->dibujar();
			this->cajaDeTextoPersonaje1->dibujar(renderText1);
			this->cajaDeTextoPersonaje2->dibujar(renderText2);
			this->dibujarPersonajeEnfocado(posX_botonera+ancho_botonera+80,posY_botonera+30, this->botonera->getIdContenidoEnfocadoParaJugador1(),ORIENTACION_IZQUIERDA);
			this->dibujarPersonajeEnfocado(80,posY_botonera+30, this->botonera->getIdContenidoEnfocadoParaJugador2(), ORIENTACION_DERECHA);

			// UPDATE screen
			SDL_RenderPresent( Renderizador::Instance()->getRenderer() );

	        frameTime = SDL_GetTicks() - frameStart;

	        if (frameTime < DELAY_TIME)
	            SDL_Delay((int)(DELAY_TIME - frameTime));
		}

		//Disable text input
		SDL_StopTextInput();

		this->IdPersonaje1Elegido = this->botonera->getIdContenidoElegidoParaJugador1();
		this->IdPersonaje2Elegido = this->botonera->getIdContenidoElegidoParaJugador2();
		this->nombrePersonaje1 = this->cajaDeTextoPersonaje1->getTexto();
		this->nombrePersonaje2 = this->cajaDeTextoPersonaje2->getTexto();

	}else {
		if ( !loadMedia_botonera )
			Logger::getInstance()->error("No se pudo cargar imagenes para la botonera en la pantalla de eleccion de personajes");
		if ( !loadMedia_cajaDeTextoPersonaje1 )
			Logger::getInstance()->error("No se pudo cargar imagenes para la caja de texto del personaje 1 en la pantalla de eleccion de personajes");
		if ( !loadMedia_cajaDeTextoPersonaje2 )
			Logger::getInstance()->error("No se pudo cargar imagenes para la caja de texto del personaje 2 en la pantalla de eleccion de personajes");
	}
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

void PantallaSeleccionarPersonaje::dibujarPersonajeEnfocado(int posX, int posY, string idPersonajeEnfocado, OrientacionSprite orientacion) {

	Vector2f vectorPosicion(posX, posY);
	PersonajeDibujable* personajeDibujable = this->personajesDibujables->find(idPersonajeEnfocado)->second;
	personajeDibujable->getSpritePersonaje()->setPosicion(vectorPosicion);
	personajeDibujable->getSpritePersonaje()->setOrientacion(orientacion);
	personajeDibujable->getSpritePersonaje()->dibujar();
	personajeDibujable->actualizar();
}

bool PantallaSeleccionarPersonaje::iniciarSalida() {

	if(this->tipoDeControl_jugador1 == "JOYSTICK"){

		map<string, bool>* estadoJoy1 = TheInputHandlerMenu::Instance()->getJoystickState(JOYSTICK1MENU);
		map<string, bool>* estadoJoy2 = TheInputHandlerMenu::Instance()->getJoystickState(JOYSTICK2MENU);

		if ( (*estadoJoy1)["JOY_PATADA_ALTA"] || (*estadoJoy2)["JOY_PATADA_ALTA"] ){
			this->salir = true;
		}
	}
	else{

		const Uint8* estadoTeclado = SDL_GetKeyboardState(NULL);
		if (estadoTeclado[SDL_SCANCODE_J])
		{
			this->salir = true;
		}
	}

	return this->salir;
}

void PantallaSeleccionarPersonaje::manejarEventoNombreDelPersonaje1(SDL_Event evento, bool* renderText1) {

	if ( this->botonera->seEligioElPersonaje1() )
	{
		if ( this->setearNombrePersonaje1 )
		{
			(*renderText1) = true;
			this->cajaDeTextoPersonaje1->setTexto(this->botonera->getIdContenidoElegidoParaJugador1());
			this->setearNombrePersonaje1 = false;
		}
		else
		{
			(*renderText1) = this->cajaDeTextoPersonaje1->manejarEvento(evento);
		}
	}
}

void PantallaSeleccionarPersonaje::manejarEventoNombreDelPersonaje2(SDL_Event evento, bool* renderText2) {

	if ( this->botonera->seEligioElPersonaje2() )
	{
		if ( this->setearNombrePersonaje2 )
		{
			(*renderText2) = true;
			this->cajaDeTextoPersonaje2->setTexto(this->botonera->getIdContenidoElegidoParaJugador2());
			this->setearNombrePersonaje2 = false;
		}else
		{
			(*renderText2) = this->cajaDeTextoPersonaje2->manejarEvento(evento);
		}
	}
}
