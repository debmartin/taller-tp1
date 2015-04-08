/*
 * Controlador.cpp
 *
 *  Created on: 23/3/2015
 *      Author: val
 */
#include "Controlador.h"

Controlador::Controlador(Personaje* pers) :
    unPersonaje(pers) {
}

void Controlador::manejar_Evento(SDL_Event &evento){

	//Si se presiona una tecla
	if( evento.type == SDL_KEYDOWN && evento.key.repeat == 0 ){
		switch( evento.key.keysym.sym ){
			case SDLK_LEFT:
				this->unPersonaje->mover(CAMINAR_IZQUIERDA);
				break;
		 	case SDLK_RIGHT:
		 		this->unPersonaje->mover(CAMINAR_DERECHA);
		 		break;
			case SDLK_UP:
				this->unPersonaje->mover(SALTAR_VERTICAL);
				break;
			case SDLK_DOWN:
				//this->unPersonaje->disminuir_velocidadY();

				break;
		}
	}
	//Si se suelta una tecla
	if( evento.type == SDL_KEYUP && evento.key.repeat == 0 ){
		switch( evento.key.keysym.sym ){
			case SDLK_LEFT:
				this->unPersonaje->mover(REPOSO);
//				this->unPersonajeDibujable.setEstado(EN_ESPERA);
				break;
			case SDLK_RIGHT:
				this->unPersonaje->mover(REPOSO);
//				this->unPersonajeDibujable.setEstado(EN_ESPERA);
				break;
			case SDLK_UP:
				this->unPersonaje->mover(REPOSO);
//				this->unPersonajeDibujable.setEstado(EN_ESPERA);
				break;
			case SDLK_DOWN:
				this->unPersonaje->mover(REPOSO);
//				this->unPersonajeDibujable.setEstado(EN_ESPERA);
				break;
		}
	}
}

void Controlador::setPersonaje(Personaje* personaje){
	this->unPersonaje = personaje;
}

//void Controlador::setPersonajeDibujable(PersonajeDibujable personaje){
//	this->unPersonajeDibujable = personaje;
//}

Controlador::~Controlador() {
	// TODO Auto-generated destructor stub
}

