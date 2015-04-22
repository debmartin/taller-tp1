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
    Logger::getInstance()->debug("Se recibe un evento de teclado.");

    if (unPersonaje->estaSaltando()) {
        Logger::getInstance()->debug("Evento invalido.");
    	return true;
    }

    if( evento.type == SDL_KEYUP && evento.key.repeat == 0 ){
        if (evento.key.keysym.sym == SDLK_r){
            Logger::getInstance()->info("Se presiona: Tecla R. Se recarga el juego.");
            return false;
        }
    }

	//Si se presiona una tecla
	if ( evento.key.repeat == 0 ){
        identificarOrden();
	}
    return true;
}

void Controlador::identificarOrden(){
    const Uint8* estadoTeclado = SDL_GetKeyboardState(NULL);

    if (estadoTeclado[SDL_SCANCODE_LEFT] && estadoTeclado[SDL_SCANCODE_UP]){
        Logger::getInstance()->debug("Se presiona: Tecla izquierda+Tecla arriba.");
        if(unPersonaje->llegoAlLimiteIzquierdo()){
            unPersonaje->saltarOblicuoIzquierdaEnLimite();
        }else{
            unPersonaje->saltarOblicuoIzquierda();
        }
    } else if (estadoTeclado[SDL_SCANCODE_RIGHT] && estadoTeclado[SDL_SCANCODE_UP]){
        Logger::getInstance()->debug("Se presiona: Tecla derecha+Tecla arriba.");
        if(unPersonaje->llegoAlLimiteDerecho()){
            unPersonaje->saltarOblicuoDerechaEnLimite();
        }else{
            unPersonaje->saltarOblicuoDerecha();
        }
    }else if (estadoTeclado[SDL_SCANCODE_LEFT] && ! unPersonaje->estaAgachado()){
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
        unPersonaje->mantenerReposo();
    }
}

void Controlador::continuarAccionPrevia(){
    if (! unPersonaje->estaEnReposo())
        return;
    identificarOrden();
}

void Controlador::setPersonaje(Personaje* personaje){
	this->unPersonaje = personaje;
}

Controlador::~Controlador() {
	// TODO Auto-generated destructor stub
}

