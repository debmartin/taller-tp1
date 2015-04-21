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

	//cout<<"Tecla:"<<evento.key.keysym.sym<<endl;
    Logger::getInstance()->debug("Se recibe un evento de teclado.");
    //cout<<"se recibe un evento de teclado"<<endl;
    if (unPersonaje->estaSaltando()) {
    	/*if(unPersonaje->terminoSalto()){
    		cout<<"termino salto"<<endl;
    		unPersonaje->setEstado(EN_ESPERA);
    	}else{*/
    	//	cout<<"no termino salto"<<endl;
    		Logger::getInstance()->debug("Evento invalido.");
    		return true;
    	//}
    }

    const Uint8* estadoTeclado = SDL_GetKeyboardState(NULL);

    if( evento.type == SDL_KEYUP && evento.key.repeat == 0 ){
        if (evento.key.keysym.sym == SDLK_r){
            Logger::getInstance()->info("Se presiona: Tecla R. Se recarga el juego.");
            return false;
        }
    }

    if(evento.type != SDL_KEYUP){
    	if(!estadoTeclado[SDL_SCANCODE_UP]){
    		eventoGuardado = evento;
    	}
    }
	//Si se presiona una tecla
	if ( evento.key.repeat == 0 ){
		cout<<"debug1"<<endl;
        if (estadoTeclado[SDL_SCANCODE_LEFT] && estadoTeclado[SDL_SCANCODE_UP]){
        	cout<<"Salto oblicuo"<<endl;
        	Logger::getInstance()->debug("Se presiona: Tecla izquierda+Tecla arriba.");
            unPersonaje->saltarOblicuoIzquierda();
        }else if (estadoTeclado[SDL_SCANCODE_RIGHT] && estadoTeclado[SDL_SCANCODE_UP]){
        	Logger::getInstance()->debug("Se presiona: Tecla derecha+Tecla arriba.");
            unPersonaje->saltarOblicuoDerecha();
        }else if (estadoTeclado[SDL_SCANCODE_LEFT] && ! unPersonaje->estaAgachado()){
        	cout<<"se detecta que tecla izquierda sigue apretada"<<endl;
        	Logger::getInstance()->debug("Se presiona: Tecla izquierda.");
            unPersonaje->caminarIzquierda();
        }else if (estadoTeclado[SDL_SCANCODE_RIGHT] && ! unPersonaje->estaAgachado()){
        	Logger::getInstance()->debug("Se presiona: Tecla derecha.");
            unPersonaje->caminarDerecha();
        }else if (estadoTeclado[SDL_SCANCODE_UP]){
        	Logger::getInstance()->debug("Se presiona: Tecla arriba.");
            unPersonaje->saltarVertical();
        }else if (estadoTeclado[SDL_SCANCODE_DOWN]){
        	Logger::getInstance()->debug("Se presiona: Tecla abajo.");
            unPersonaje->agacharse();

        }else{
        	cout<<"reposo"<<endl;
            unPersonaje->mantenerReposo();
        }
/*	}else if (estadoTeclado[SDL_SCANCODE_LEFT]){
		cout<<"se reconoce izquierda"<<endl;
		unPersonaje->caminarIzquierda();*/
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

SDL_Event Controlador::obtenerUltimoEvento(){
	return this->eventoGuardado;
}

Controlador::~Controlador() {
	// TODO Auto-generated destructor stub
}

