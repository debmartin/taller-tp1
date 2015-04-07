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
				this->unPersonaje->setTrayectoria(new MRU(unPersonaje->getPosicion(), Vector2f(-180.0f, 0.0f)));
				break;
		 	case SDLK_RIGHT:
		 		this->unPersonaje->setTrayectoria(new MRU(unPersonaje->getPosicion(), Vector2f(180.0f, 0.0f)));
		 		break;
			case SDLK_UP:
				this->unPersonaje->setTrayectoria(new MRUV(unPersonaje->getPosicion(), Vector2f(0,-800.0f), Vector2f(0,1600.0f)));
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
				this->unPersonaje->setTrayectoria(new Reposo(unPersonaje->getPosicion()));
//				this->unPersonajeDibujable.setEstado(EN_ESPERA);
				break;
			case SDLK_RIGHT:
				this->unPersonaje->setTrayectoria(new Reposo(unPersonaje->getPosicion()));
//				this->unPersonajeDibujable.setEstado(EN_ESPERA);
				break;
			case SDLK_UP:
				this->unPersonaje->setTrayectoria(new Reposo(unPersonaje->getPosicion()));
//				this->unPersonajeDibujable.setEstado(EN_ESPERA);
				break;
			case SDLK_DOWN:
				this->unPersonaje->setTrayectoria(new Reposo(unPersonaje->getPosicion()));
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

