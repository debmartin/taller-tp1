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

#define BOTON_ARROJAR_ARMA SDLK_0
#define BOTON_GOLPE_ALTO SDLK_1
#define BOTON_PATADA_ALTA SDLK_2
#define BOTON_BLOQUEAR SDLK_3
#define TIEMPO_BLOQUEADO 200

ControladorPersonaje::ControladorPersonaje(Personaje* jugador1, Personaje* jugador2) :
    personaje1(jugador1), personaje2(jugador2) {
	ControladorJoystick::Instance()->initialiseJoysticks();
}


bool ControladorPersonaje::manejar_Evento(SDL_Event &evento){
    Logger::getInstance()->debug("Se recibe un evento de teclado.");

    //Cargo los botones de los joysticks
    TheInputHandler::Instance()->handleEventsJoysticks(evento);
/*
    if (personaje1->estaSaltando() || personaje2->estaSaltando()) {
        Logger::getInstance()->error("Evento invalido.");
    	return true;
    }*/

    if(!personaje1->estaBloqueado() && !personaje1->estaSaltando()){
    	identificarOrdenJoystickPersonaje1(personaje1);
    }
    if(!personaje2->estaBloqueado() && !personaje2->estaSaltando()){
    	identificarOrdenJoystickPersonaje2(personaje2);
    }

	//Si se presiona una tecla
    /*
	if ( evento.key.repeat == 0 ){
		if(!personaje1->estaBloqueado()){
			identificarOrdenPersonaje(personaje1);
		}
		if(!personaje2->estaBloqueado()){
			identificarOrdenPersonaje(personaje2);
		}
	}*/
    return true;
}

void ControladorPersonaje::identificarOrdenJoystickPersonaje1(Personaje* personaje){
	std::map<string, bool>* estadoJoy1 = TheInputHandler::Instance()->getJoystickState(JOYSTICK1);

	    if ((*estadoJoy1)["JOY_IZQUIERDA"] && (*estadoJoy1)["JOY_ARRIBA"]){
	        Logger::getInstance()->debug("Se presiona: Tecla izquierda+Tecla arriba.");
	        personaje->saltarOblicuoIzquierda();
	    } else if((*estadoJoy1)["JOY_DERECHA"] && (*estadoJoy1)["JOY_ARRIBA"]){
	        Logger::getInstance()->debug("Se presiona: Tecla derecha+Tecla arriba.");
	        personaje->saltarOblicuoDerecha();
	    }else if ((*estadoJoy1)["JOY_IZQUIERDA"] && ! personaje->estaAgachado()){
	        Logger::getInstance()->debug("Se presiona: Tecla izquierda.");
	        personaje->caminarIzquierda();
	    }else if ((*estadoJoy1)["JOY_DERECHA"] && ! personaje->estaAgachado()){
	        Logger::getInstance()->debug("Se presiona: Tecla derecha.");
	        personaje->caminarDerecha();
	    }else if((*estadoJoy1)["JOY_DEFENSA"] && personaje->estaAgachado()){
	        personaje->defenderAgachado();
	    }else if(((*estadoJoy1)["JOY_PINIA_ALTA"] || (*estadoJoy1)["JOY_PINIA_BAJA"]) && personaje->estaAgachado()){
	        personaje->gancho();
	    }else if(((*estadoJoy1)["JOY_PATADA_ALTA"] || (*estadoJoy1)["JOY_PATADA_BAJA"]) && personaje->estaAgachado()){
	    	personaje->patadaAltaAgachado();
	    }else if ((*estadoJoy1)["JOY_ARRIBA"]){
	        Logger::getInstance()->debug("Se presiona: Tecla arriba.");
	        personaje->saltarVertical();
	    }/*else if(((*estadoJoy1)["JOY_PINIA_ALTA"] || (*estadoJoy1)["JOY_PINIA_ALTA"]) && personaje->estaSaltando()){
	    	personaje->piniaSaltandoVertical();
	    }*/else if ((*estadoJoy1)["JOY_ABAJO"]){
	        Logger::getInstance()->debug("Se presiona: Tecla abajo.");
	        personaje->agacharse();
	    }else if((*estadoJoy1)["JOY_PODER"]){
	        personaje->arrojarArma();
	    }else if((*estadoJoy1)["JOY_PINIA_ALTA"]){
	        personaje->piniaAlta();
	    }else if((*estadoJoy1)["JOY_PATADA_ALTA"]){
	    	cout<<"patada alta"<<endl;
	        personaje->patadaAlta();
	    }else if((*estadoJoy1)["JOY_PINIA_BAJA"]){
	        personaje->piniaBaja();
	    }else if((*estadoJoy1)["JOY_PATADA_BAJA"]){
	        personaje->patadaBaja();
	    }else if((*estadoJoy1)["JOY_DEFENSA"]){
	        personaje->defender();
	    }
	    /*else if(SDL_JoystickGetButton(joyAct, BOTON_BLOQUEAR)){
	    	personaje->bloquearPersonaje(TIEMPO_BLOQUEADO);
	    }*/else{
	        personaje->mantenerReposo();
	    }
}

void ControladorPersonaje::identificarOrdenJoystickPersonaje2(Personaje* personaje){
	std::map<string, bool>* estadoJoy2 = TheInputHandler::Instance()->getJoystickState(JOYSTICK2);

	    if ((*estadoJoy2)["JOY_IZQUIERDA"] && (*estadoJoy2)["JOY_ARRIBA"]){
	        Logger::getInstance()->debug("Se presiona: Tecla izquierda+Tecla arriba.");
	        personaje->saltarOblicuoIzquierda();
	    } else if((*estadoJoy2)["JOY_DERECHA"] && (*estadoJoy2)["JOY_ARRIBA"]){
	        Logger::getInstance()->debug("Se presiona: Tecla derecha+Tecla arriba.");
	        personaje->saltarOblicuoDerecha();
	    }else if ((*estadoJoy2)["JOY_IZQUIERDA"] && ! personaje->estaAgachado()){
	        Logger::getInstance()->debug("Se presiona: Tecla izquierda.");
	        personaje->caminarIzquierda();
	    }else if ((*estadoJoy2)["JOY_DERECHA"] && ! personaje->estaAgachado()){
	        Logger::getInstance()->debug("Se presiona: Tecla derecha.");
	        personaje->caminarDerecha();
	    }else if((*estadoJoy2)["JOY_DEFENSA"] && personaje->estaAgachado()){
	        personaje->defenderAgachado();
	    }else if(((*estadoJoy2)["JOY_PINIA_ALTA"] || (*estadoJoy2)["JOY_PINIA_BAJA"]) && personaje->estaAgachado()){
	    	personaje->gancho();
	    }else if(((*estadoJoy2)["JOY_PATADA_ALTA"] || (*estadoJoy2)["JOY_PATADA_BAJA"]) && personaje->estaAgachado()){
	    	personaje->patadaAltaAgachado();
	    }else if ((*estadoJoy2)["JOY_ARRIBA"]){
	        Logger::getInstance()->debug("Se presiona: Tecla arriba.");
	        personaje->saltarVertical();
	    }/*else if(((*estadoJoy2)["JOY_PINIA_ALTA"] || (*estadoJoy2)["JOY_PINIA_ALTA"]) && personaje->estaSaltando()){
	    	personaje->piniaSaltandoVertical();
	    }*/else if ((*estadoJoy2)["JOY_ABAJO"]){
	        Logger::getInstance()->debug("Se presiona: Tecla abajo.");
	        personaje->agacharse();
	    }else if((*estadoJoy2)["JOY_PODER"]){
	        personaje->arrojarArma();
	    }else if((*estadoJoy2)["JOY_PINIA_ALTA"]){
	        personaje->piniaAlta();
	    }else if((*estadoJoy2)["JOY_PATADA_ALTA"]){
	    	cout<<"patada alta"<<endl;
	        personaje->patadaAlta();
	    }else if((*estadoJoy2)["JOY_PINIA_BAJA"]){
	        personaje->piniaBaja();
	    }else if((*estadoJoy2)["JOY_PATADA_BAJA"]){
	        personaje->patadaBaja();
	    }else if((*estadoJoy2)["JOY_DEFENSA"]){
	        personaje->defender();
	    }
	    /*else if(SDL_JoystickGetButton(joyAct, BOTON_BLOQUEAR)){
	    	personaje->bloquearPersonaje(TIEMPO_BLOQUEADO);
	    }*/else{
	        personaje->mantenerReposo();
	    }
}
void ControladorPersonaje::identificarOrdenPersonaje(Personaje* personaje){
}

void ControladorPersonaje::identificarOrdenPersonaje1(){
    const Uint8* estadoTeclado = SDL_GetKeyboardState(NULL);

    /**
     * Codigos numericos de las teclas
    SDL_SCANCODE_RIGHT = 79,
    SDL_SCANCODE_LEFT = 80,
    SDL_SCANCODE_DOWN = 81,
    SDL_SCANCODE_UP = 82,
    SDL_SCANCODE_F = 9,
    SDL_SCANCODE_G = 10,
    SDL_SCANCODE_H = 11,
    SDL_SCANCODE_N = 17,
     *
     */

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
    }else if(estadoTeclado[SDL_SCANCODE_G] && personaje1->estaAgachado()){
       	cout<<"gancho"<<endl;
        personaje1->gancho();
    }else if (estadoTeclado[SDL_SCANCODE_DOWN]){
        Logger::getInstance()->debug("Se presiona: Tecla abajo.");
        personaje1->agacharse();
    }else if(estadoTeclado[SDL_SCANCODE_F]){
    	personaje1->arrojarArma();
    }else if(estadoTeclado[SDL_SCANCODE_G]){
        personaje1->piniaAlta();
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

    /**
     * Codigos numericos de las teclas
    SDL_SCANCODE_A = 4,
    SDL_SCANCODE_D = 7,
    SDL_SCANCODE_W = 26,
    SDL_SCANCODE_S = 22,
    SDL_SCANCODE_C = 6,
    SDL_SCANCODE_V = 25,
    SDL_SCANCODE_B = 5,
    SDL_SCANCODE_M = 16,
     *
     */

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
    }else if(estadoTeclado[SDL_SCANCODE_G] && personaje2->estaAgachado()){
        cout<<"gancho"<<endl;
        personaje2->gancho();
    }else if (estadoTeclado[SDL_SCANCODE_S]){
        Logger::getInstance()->debug("Se presiona: Tecla abajo.");
        personaje2->agacharse();
    }else if(estadoTeclado[SDL_SCANCODE_C]){
      	personaje2->arrojarArma();
    }else if(estadoTeclado[SDL_SCANCODE_V]){
        personaje2->piniaAlta();
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
    //identificarOrdenPersonaje(personaje1);
    identificarOrdenPersonaje1();
}

void ControladorPersonaje::continuarAccionPreviaPersonaje2(){
    if (! personaje2->estaEnReposo())
        return;
    //identificarOrdenPersonaje(personaje2);
    identificarOrdenPersonaje2();
}

ControladorPersonaje::~ControladorPersonaje() {
	SDL_JoystickClose(joysticks[personaje1]);
	SDL_JoystickClose(joysticks[personaje2]);
}
