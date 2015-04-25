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

ControladorPersonaje::ControladorPersonaje() {
	Personaje* personaje1 = new Personaje();
	Personaje* personaje2 = new Personaje();
}


bool ControladorPersonaje::manejar_Evento(SDL_Event &evento){
    Logger::getInstance()->debug("Se recibe un evento de teclado.");

    if (personaje1->estaSaltando()) {
        Logger::getInstance()->debug("Evento invalido.");
    	return true;
    }

	//Si se presiona una tecla
	if ( evento.key.repeat == 0 ){
        identificarOrden();
	}
    return true;
}

void ControladorPersonaje::identificarOrden(){
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
    }else{
        personaje1->mantenerReposo();
    }
}

void ControladorPersonaje::continuarAccionPrevia(){
    if (! personaje1->estaEnReposo())
        return;
    identificarOrden();
}

ControladorPersonaje::~ControladorPersonaje() {
	// TODO Auto-generated destructor stub
}

void ControladorPersonaje::agregarPersonaje1(Personaje* personaje1) {
	this->personaje1 = personaje1;
}

void ControladorPersonaje::agregarPersonaje2(Personaje* personaje2) {
	this->personaje2 = personaje2;
}
