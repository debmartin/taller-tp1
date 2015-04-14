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
    SDL_PumpEvents();
    const Uint8* estadoTeclado = SDL_GetKeyboardState(NULL);
	//Si se presiona una tecla
	if( evento.key.repeat == 0 ){
		cout<<"Entro tecla"<<endl;

        if (estadoTeclado[SDL_SCANCODE_LEFT] && estadoTeclado[SDL_SCANCODE_UP])
            unPersonaje->saltarOblicuoIzquierda();
        else if (estadoTeclado[SDL_SCANCODE_RIGHT] && estadoTeclado[SDL_SCANCODE_UP])
            unPersonaje->saltarOblicuoDerecha();
        else if (estadoTeclado[SDL_SCANCODE_LEFT])
            unPersonaje->caminarIzquierda();
        else if (estadoTeclado[SDL_SCANCODE_RIGHT])
            unPersonaje->caminarDerecha();
        else if (estadoTeclado[SDL_SCANCODE_UP])
            unPersonaje->saltarVertical();
        else if (estadoTeclado[SDL_SCANCODE_DOWN])
            unPersonaje->agacharse();
        else
            unPersonaje->mantenerReposo();
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
}

void Controlador::setPersonaje(Personaje* personaje){
	this->unPersonaje = personaje;
}

Controlador::~Controlador() {
	// TODO Auto-generated destructor stub
}

