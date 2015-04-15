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

bool Controlador::manejar_Evento(SDL_Event &evento){
//    SDL_PumpEvents();
    const Uint8* estadoTeclado = SDL_GetKeyboardState(NULL);
	//Si se presiona una tecla
	if ( evento.key.repeat == 0 ){
    	Logger::getInstance()->debug("Se recibe un evento de teclado.");

        if (estadoTeclado[SDL_SCANCODE_LEFT] && estadoTeclado[SDL_SCANCODE_UP]){
        	Logger::getInstance()->debug("Se presiona: Tecla izquierda+Tecla arriba.");
            unPersonaje->saltarOblicuoIzquierda();
        }else if (estadoTeclado[SDL_SCANCODE_RIGHT] && estadoTeclado[SDL_SCANCODE_UP]){
        	Logger::getInstance()->debug("Se presiona: Tecla derecha+Tecla arriba.");
            unPersonaje->saltarOblicuoDerecha();
        }else if (estadoTeclado[SDL_SCANCODE_LEFT]){
        	Logger::getInstance()->debug("Se presiona: Tecla izquierda.");
            unPersonaje->caminarIzquierda();
        }else if (estadoTeclado[SDL_SCANCODE_RIGHT]){
        	Logger::getInstance()->debug("Se presiona: Tecla derecha.");
            unPersonaje->caminarDerecha();
        }else if (estadoTeclado[SDL_SCANCODE_UP]){
        	Logger::getInstance()->debug("Se presiona: Tecla arriba.");
            unPersonaje->saltarVertical();
        }else if (estadoTeclado[SDL_SCANCODE_DOWN]){
        	Logger::getInstance()->debug("Se presiona: Tecla abajo.");
            unPersonaje->agacharse();
        } else if (estadoTeclado[SDL_SCANCODE_R]) {
            Logger::getInstance()->debug("Se presiona: Tecla R.");
            return false;
        }else{
        	Logger::getInstance()->debug("No se presiona tecla.");
            unPersonaje->mantenerReposo();
        }
	}
//	//Si se suelta una tecla
//	if( evento.type == SDL_KEYUP && evento.key.repeat == 0 ){
//		switch( evento.key.keysym.sym ){
//			case SDLK_LEFT:
//			case SDLK_RIGHT:
//			case SDLK_DOWN:
//				this->unPersonaje->mantenerReposo();
//				break;
//            case SDLK_UP:
//        if (estadoTeclado[SDL_SCANCODE_RIGHT])
//            unPersonaje->caminarDerecha();
//        else if (estadoTeclado[SDL_SCANCODE_LEFT])
//            unPersonaje->caminarIzquierda();
//		}
//	}
    return true;
}

void Controlador::setPersonaje(Personaje* personaje){
	this->unPersonaje = personaje;
}

Controlador::~Controlador() {
	// TODO Auto-generated destructor stub
}

