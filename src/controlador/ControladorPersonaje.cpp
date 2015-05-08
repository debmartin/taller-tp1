/*
 * ControladorPersonaje.cpp
 *
 *  Created on: 25/4/2015
 *      Author: ariel
 */

#include "ControladorPersonaje.h"

#include <SDL2/begin_code.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_scancode.h>

#include "../modelo/Personaje.h"
#include "../utils/Logger.h"

ControladorPersonaje::ControladorPersonaje(Personaje* jugador1, Personaje* jugador2) :
    personaje1(jugador1), personaje2(jugador2) {
}


bool ControladorPersonaje::manejar_Evento(SDL_Event &evento){
    Logger::getInstance()->debug("Se recibe un evento de teclado.");

    if (personaje1->estaSaltando() || personaje2->estaSaltando()) {
        Logger::getInstance()->error("Evento invalido.");
    	return true;
    }

	//Si se presiona una tecla
	if ( evento.key.repeat == 0 ){
		if(!personaje1->estaBloqueado()){
			identificarOrdenPersonaje1();
		}
		if(!personaje2->estaBloqueado()){
			identificarOrdenPersonaje2();
		}
	}
    return true;
}

void ControladorPersonaje::identificarOrdenPersonaje1(){
    const Uint8* estadoTeclado = SDL_GetKeyboardState(NULL);

    if (estadoTeclado[SDL_SCANCODE_LEFT] && estadoTeclado[SDL_SCANCODE_UP]){
        Logger::getInstance()->debug("Se presiona: Tecla izquierda+Tecla arriba.");
        personaje1->saltarOblicuoIzquierda();
    } else if (estadoTeclado[SDL_SCANCODE_RIGHT] && estadoTeclado[SDL_SCANCODE_UP]){
        Logger::getInstance()->debug("Se presiona: Tecla derecha+Tecla arriba.");
        personaje1->saltarOblicuoDerecha();
    }else if (estadoTeclado[SDL_SCANCODE_LEFT] && ! personaje1->estaAgachado()){
        Logger::getInstance()->debug("Se presiona: Tecla izquierda.");
        personaje1->caminarIzquierda();
    }else if (estadoTeclado[SDL_SCANCODE_RIGHT] && ! personaje1->estaAgachado()){
        Logger::getInstance()->debug("Se presiona: Tecla derecha.");
        personaje1->caminarDerecha();
    }else if (estadoTeclado[SDL_SCANCODE_UP]){
        Logger::getInstance()->debug("Se presiona: Tecla arriba.");
        personaje1->saltarVertical();
    }else if (estadoTeclado[SDL_SCANCODE_DOWN]){
        Logger::getInstance()->debug("Se presiona: Tecla abajo.");
        personaje1->agacharse();
    }else if(estadoTeclado[SDL_SCANCODE_F]){
    	personaje1->arrojarArma();
    }else if(estadoTeclado[SDL_SCANCODE_G]){
        personaje1->golpeAlto();
    }else if(estadoTeclado[SDL_SCANCODE_H]){
        personaje1->patadaAlta();
    }else if(estadoTeclado[SDL_SCANCODE_N]){
    	personaje1->bloquearPersonaje(200);
    }else{
        personaje1->mantenerReposo();
    }

}

void ControladorPersonaje::identificarOrdenPersonaje2(){
    const Uint8* estadoTeclado = SDL_GetKeyboardState(NULL);

    if (estadoTeclado[SDL_SCANCODE_A] && estadoTeclado[SDL_SCANCODE_W]){
        Logger::getInstance()->debug("Se presiona: Tecla izquierda+Tecla arriba.");
        personaje2->saltarOblicuoIzquierda();
    } else if (estadoTeclado[SDL_SCANCODE_D] && estadoTeclado[SDL_SCANCODE_W]){
        Logger::getInstance()->debug("Se presiona: Tecla derecha+Tecla arriba.");
        personaje2->saltarOblicuoDerecha();
    }else if (estadoTeclado[SDL_SCANCODE_A] && ! personaje2->estaAgachado()){
        Logger::getInstance()->debug("Se presiona: Tecla izquierda.");
        personaje2->caminarIzquierda();
    }else if (estadoTeclado[SDL_SCANCODE_D] && ! personaje2->estaAgachado()){
        Logger::getInstance()->debug("Se presiona: Tecla derecha.");
        personaje2->caminarDerecha();
    }else if (estadoTeclado[SDL_SCANCODE_W]){
        Logger::getInstance()->debug("Se presiona: Tecla arriba.");
        personaje2->saltarVertical();
    }else if (estadoTeclado[SDL_SCANCODE_S]){
        Logger::getInstance()->debug("Se presiona: Tecla abajo.");
        personaje2->agacharse();
    }else if(estadoTeclado[SDL_SCANCODE_C]){
      	personaje2->arrojarArma();
    }else if(estadoTeclado[SDL_SCANCODE_V]){
        personaje2->golpeAlto();
    }else if(estadoTeclado[SDL_SCANCODE_B]){
        personaje2->patadaAlta();
    }else if(estadoTeclado[SDL_SCANCODE_M]){
        personaje2->bloquearPersonaje(200);
    }else{
        personaje2->mantenerReposo();
    }

}

void ControladorPersonaje::continuarAccionPreviaPersonaje1(){
    if (! personaje1->estaEnReposo())
        return;
    identificarOrdenPersonaje1();
}

void ControladorPersonaje::continuarAccionPreviaPersonaje2(){
    if (! personaje2->estaEnReposo())
        return;
    identificarOrdenPersonaje2();
}

ControladorPersonaje::~ControladorPersonaje() {
	// TODO Auto-generated destructor stub
}
