/*
 * Controlador.cpp
 *
 *  Created on: 23/3/2015
 *      Author: val
 */
#include "Controlador.h"

void Controlador::manejar_Evento(SDL_Event &evento){
	//Si se presiona una tecla
	if( evento.type == SDL_KEYDOWN && evento.key.repeat == 0 ){
		switch( evento.key.keysym.sym ){
			case SDLK_LEFT:
				this->unPersonaje.disminuir_velocidadX();
				this->unPersonajeDibujable.setEstado(caminando_izquierda);
				break;
		 	case SDLK_RIGHT:
		 		this->unPersonaje.aumentar_velocidadX();
		 		this->unPersonajeDibujable.setEstado(caminando_derecha);
		 		break;
			case SDLK_UP:
				this->unPersonaje.aumentar_velocidadY();
				this->unPersonajeDibujable.setEstado(saltando);
				break;
			case SDLK_DOWN:
				this->unPersonaje.disminuir_velocidadY();
				this->unPersonajeDibujable.setEstado(saltando);
				break;
		}
	}
	//Si se suelta una tecla
	if( evento.type == SDL_KEYUP && evento.key.repeat == 0 ){
		switch( evento.key.keysym.sym ){
			case SDLK_LEFT:
				this->unPersonaje.aumentar_velocidadX();
				this->unPersonajeDibujable.setEstado(caminando_izquierda);
				break;
			case SDLK_RIGHT:
				this->unPersonaje.disminuir_velocidadX();
				this->unPersonajeDibujable.setEstado(caminando_izquierda);
				break;
			case SDLK_UP:
				this->unPersonaje.disminuir_velocidadY();
				this->unPersonajeDibujable.setEstado(caminando_izquierda);
				break;
			case SDLK_DOWN:
				this->unPersonaje.aumentar_velocidadY();
				this->unPersonajeDibujable.setEstado(caminando_izquierda);
				break;
		}
	}
}

Controlador::~Controlador() {
	// TODO Auto-generated destructor stub
}

