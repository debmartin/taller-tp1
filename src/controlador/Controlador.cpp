/*
 * Controlador.cpp
 *
 *  Created on: 23/3/2015
 *      Author: val
 */
#include "Controlador.h"

void Controlador::manejar_Evento(SDL_Event &evento){
	//Si se presiono una tecla
	if( evento.type == SDL_KEYDOWN && evento.key.repeat == 0 ){
		switch( evento.key.keysym.sym )
		{
			case SDLK_LEFT: this->unPersonaje.caminarIzquierda(); break;
		 	case SDLK_RIGHT: this->unPersonaje.caminarDerecha(); break;
			case SDLK_UP: this->unPersonaje.moverArriba(); break;
			case SDLK_DOWN: this->unPersonaje.moverAbajo(); break;
		}
	}
}

Controlador::~Controlador() {
	// TODO Auto-generated destructor stub
}

