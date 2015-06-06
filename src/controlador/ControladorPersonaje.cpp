/*
 * ControladorPersonaje.cpp
 *
 *  Created on: 25/4/2015
 *      Author: ariel
 */

#include "ControladorPersonaje.h"

#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_scancode.h>
#include <iostream>
#include <string>

#include "../modelo/Jugador.h"
#include "../utils/Logger.h"
#include "Control.h"

ControladorPersonaje::ControladorPersonaje(Jugador* jugador1, Jugador* jugador2, string tipoControl) :
    personaje1(jugador1->getPersonaje()), personaje2(jugador2->getPersonaje()) {
	tipoDeControl = tipoControl;
	ControladorJoystick::Instance()->initialiseJoysticks(jugador1->getControl()->getCorrespondenciaTeclas(),
														jugador1->getControl()->getCorrespondenciaEjes(),
														jugador2->getControl()->getCorrespondenciaTeclas(),
														jugador2->getControl()->getCorrespondenciaEjes());
}


bool ControladorPersonaje::manejar_Evento(SDL_Event &evento){
    Logger::getInstance()->debug("Se recibe un evento de teclado.");


    //Cargo los botones de los joysticks
    TheInputHandler::Instance()->handleEventsJoysticks(evento);

    if(tipoDeControl == "JOYSTICK"){
    	if(!personaje1->estaBloqueado() && !personaje1->estaEnCaida()){
    		identificarOrdenJoystickPersonaje(personaje1, JOYSTICK1);
    	}
    	if(!personaje2->estaBloqueado() && !personaje2->estaEnCaida()){
    		identificarOrdenJoystickPersonaje(personaje2, JOYSTICK2);
    	}
	}else{
		//Si se presiona una tecla
		if ( evento.key.repeat == 0 ){
			if(!personaje1->estaBloqueado() ){
				identificarOrdenPersonaje1();
			}
			if(!personaje2->estaBloqueado()){
				identificarOrdenPersonaje2();
			}
		}
	}
    return true;
}

void ControladorPersonaje::identificarOrdenJoystickPersonaje(Personaje* personaje, JoyNumber numeroJoystick){
	std::map<string, bool>* estadoJoy = TheInputHandler::Instance()->getJoystickState(numeroJoystick);

	if(TheInputHandler::Instance()->combo_completado()){
		personaje->ejecutarCombo(TheInputHandler::Instance()->informar_combo());
		return;
	}

	if (personaje->estaSaltando()){
		if(((*estadoJoy)["JOY_PINIA_ALTA"] || (*estadoJoy)["JOY_PINIA_BAJA"]) && personaje->estaSaltandoVertical()){
			personaje->piniaSaltandoVertical();
		}if(((*estadoJoy)["JOY_PATADA_ALTA"] || (*estadoJoy)["JOY_PATADA_BAJA"]) && personaje->estaSaltandoVertical()){
			personaje->patadaSaltandoVertical();
		}else if(((*estadoJoy)["JOY_PINIA_ALTA"] || (*estadoJoy)["JOY_PINIA_BAJA"]) && personaje->estaSaltandoDiagonalDerecha()){
    		personaje->piniaSaltandoDiagonalDerecha();
    	}else if(((*estadoJoy)["JOY_PATADA_ALTA"] || (*estadoJoy)["JOY_PATADA_BAJA"]) && personaje->estaSaltandoDiagonalDerecha()){
    		personaje->patadaSaltandoDiagonalDerecha();
    	}else if(((*estadoJoy)["JOY_PINIA_ALTA"] || (*estadoJoy)["JOY_PINIA_BAJA"]) && personaje->estaSaltandoDiagonalIzquierda()){
    		personaje->piniaSaltandoDiagonalIzquierda();
    	}else if(((*estadoJoy)["JOY_PATADA_ALTA"] || (*estadoJoy)["JOY_PATADA_BAJA"]) && personaje->estaSaltandoDiagonalIzquierda()){
    		personaje->patadaSaltandoDiagonalIzquierda();
    	}
	}else{
	    if ((*estadoJoy)["JOY_IZQUIERDA"] && (*estadoJoy)["JOY_ARRIBA"]){
	        Logger::getInstance()->debug("Se presiona: Tecla izquierda+Tecla arriba.");
	        personaje->saltarOblicuoIzquierda();
	    } else if((*estadoJoy)["JOY_DERECHA"] && (*estadoJoy)["JOY_ARRIBA"]){
	        Logger::getInstance()->debug("Se presiona: Tecla derecha+Tecla arriba.");
	        personaje->saltarOblicuoDerecha();
	    }else if ((*estadoJoy)["JOY_IZQUIERDA"] && ! personaje->estaAgachado()){
	        Logger::getInstance()->debug("Se presiona: Tecla izquierda.");
	        personaje->caminarIzquierda();
	    }else if ((*estadoJoy)["JOY_DERECHA"] && ! personaje->estaAgachado()){
	        Logger::getInstance()->debug("Se presiona: Tecla derecha.");
	        personaje->caminarDerecha();
	    }else if((*estadoJoy)["JOY_DEFENSA"] && personaje->estaAgachado()){
	        personaje->defenderAgachado();
	    }else if(((*estadoJoy)["JOY_PINIA_ALTA"] || (*estadoJoy)["JOY_PINIA_BAJA"]) && personaje->estaAgachado()){
	    	personaje->gancho();
	    }else if(((*estadoJoy)["JOY_PATADA_ALTA"] || (*estadoJoy)["JOY_PATADA_BAJA"]) && personaje->estaAgachado()){
	    	personaje->patadaAltaAgachado();
	    }else if ((*estadoJoy)["JOY_ARRIBA"]){
	        Logger::getInstance()->debug("Se presiona: Tecla arriba.");
	        personaje->saltarVertical();
	    }else if ((*estadoJoy)["JOY_ABAJO"]){
	        Logger::getInstance()->debug("Se presiona: Tecla abajo.");
	        personaje->agacharse();
	    }else if((*estadoJoy)["JOY_PINIA_ALTA"]){
	        personaje->piniaAlta();
	    }else if((*estadoJoy)["JOY_PATADA_ALTA"]){
	        personaje->patadaAlta();
	    }else if((*estadoJoy)["JOY_PINIA_BAJA"]){
	    	personaje->deslizar();
	        //personaje->piniaBaja();
	    }else if((*estadoJoy)["JOY_PATADA_BAJA"]){
	        personaje->patadaBaja();
	    }else if((*estadoJoy)["JOY_DEFENSA"]){
	        personaje->defender();
	    }/*else if((*estadoJoy)["JOY_PODER"]){
	        personaje->arrojarArma();
	    }*/
	    else{
	        personaje->mantenerReposo();
	    }
	}
	if((*estadoJoy)["JOY_PODER"]){
	        personaje->arrojarArma();
	}
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
    if (personaje1->estaSaltando()){
    	if((estadoTeclado[SDL_SCANCODE_G] || estadoTeclado[SDL_SCANCODE_J]) && personaje1->estaSaltandoVertical()){
    		personaje1->piniaSaltandoVertical();
    	}else if((estadoTeclado[SDL_SCANCODE_H] || estadoTeclado[SDL_SCANCODE_K]) && personaje1->estaSaltandoVertical()){
    		personaje1->patadaSaltandoVertical();
    	}else if((estadoTeclado[SDL_SCANCODE_G] || estadoTeclado[SDL_SCANCODE_J]) && personaje1->estaSaltandoDiagonalDerecha()){
    		personaje1->piniaSaltandoDiagonalDerecha();
    	}else if((estadoTeclado[SDL_SCANCODE_H] || estadoTeclado[SDL_SCANCODE_K]) && personaje1->estaSaltandoDiagonalDerecha()){
    		personaje1->patadaSaltandoDiagonalDerecha();
    	}else if((estadoTeclado[SDL_SCANCODE_G] || estadoTeclado[SDL_SCANCODE_J]) && personaje1->estaSaltandoDiagonalIzquierda()){
    		personaje1->piniaSaltandoDiagonalIzquierda();
    	}else if((estadoTeclado[SDL_SCANCODE_H] || estadoTeclado[SDL_SCANCODE_K]) && personaje1->estaSaltandoDiagonalIzquierda()){
    		personaje1->patadaSaltandoDiagonalIzquierda();
    	}
    }else{
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
		}else if(estadoTeclado[SDL_SCANCODE_L] && personaje1->estaAgachado()){
			personaje1->defenderAgachado();
		}else if((estadoTeclado[SDL_SCANCODE_G] || estadoTeclado[SDL_SCANCODE_J] ) && personaje1->estaAgachado()){
			personaje1->gancho();
		}else if((estadoTeclado[SDL_SCANCODE_H] || estadoTeclado[SDL_SCANCODE_K]) && personaje1->estaAgachado()){
			personaje1->patadaAltaAgachado();
		}else if (estadoTeclado[SDL_SCANCODE_UP]){
			Logger::getInstance()->debug("Se presiona: Tecla arriba.");
			personaje1->saltarVertical();
		}else if (estadoTeclado[SDL_SCANCODE_DOWN]){
			Logger::getInstance()->debug("Se presiona: Tecla abajo.");
			personaje1->agacharse();
		}else if(estadoTeclado[SDL_SCANCODE_G]){
			personaje1->piniaAlta();
		}else if(estadoTeclado[SDL_SCANCODE_H]){
			personaje1->patadaAlta();
		}else if(estadoTeclado[SDL_SCANCODE_J]){
			personaje1->deslizar();
			//personaje1->piniaBaja();
		}else if(estadoTeclado[SDL_SCANCODE_K]){
			personaje1->patadaBaja();
		}else if(estadoTeclado[SDL_SCANCODE_L]){
			personaje1->defender();
		}else{
			personaje1->mantenerReposo();
		}
    }
    if(estadoTeclado[SDL_SCANCODE_F]){
			personaje1->arrojarArma();
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
    if (personaje2->estaSaltando()){
       if((estadoTeclado[SDL_SCANCODE_C] || estadoTeclado[SDL_SCANCODE_B]) && personaje2->estaSaltandoVertical()){
        	personaje2->piniaSaltandoVertical();
       }else if((estadoTeclado[SDL_SCANCODE_V] || estadoTeclado[SDL_SCANCODE_N]) && personaje2->estaSaltandoVertical()){
        	personaje2->patadaSaltandoVertical();
       }else if((estadoTeclado[SDL_SCANCODE_C] || estadoTeclado[SDL_SCANCODE_B]) && personaje2->estaSaltandoDiagonalDerecha()){
   			personaje2->piniaSaltandoDiagonalDerecha();
       }else if((estadoTeclado[SDL_SCANCODE_V] || estadoTeclado[SDL_SCANCODE_N]) && personaje2->estaSaltandoDiagonalDerecha()){
    	   personaje2->patadaSaltandoDiagonalDerecha();
       }else if((estadoTeclado[SDL_SCANCODE_C] || estadoTeclado[SDL_SCANCODE_B]) && personaje2->estaSaltandoDiagonalIzquierda()){
    	   personaje2->piniaSaltandoDiagonalIzquierda();
       }else if((estadoTeclado[SDL_SCANCODE_V] || estadoTeclado[SDL_SCANCODE_N]) && personaje2->estaSaltandoDiagonalIzquierda()){
    	   personaje2->patadaSaltandoDiagonalIzquierda();
       }
    }else{
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
		}else if(estadoTeclado[SDL_SCANCODE_M] && personaje2->estaAgachado()){
			personaje2->defenderAgachado();
		}else if((estadoTeclado[SDL_SCANCODE_C] || estadoTeclado[SDL_SCANCODE_B] ) && personaje2->estaAgachado()){
			personaje2->gancho();
		}else if((estadoTeclado[SDL_SCANCODE_V] || estadoTeclado[SDL_SCANCODE_N]) && personaje2->estaAgachado()){
			personaje2->patadaAltaAgachado();
		}else if (estadoTeclado[SDL_SCANCODE_W]){
			Logger::getInstance()->debug("Se presiona: Tecla arriba.");
			personaje2->saltarVertical();
		}else if (estadoTeclado[SDL_SCANCODE_S]){
			Logger::getInstance()->debug("Se presiona: Tecla abajo.");
			personaje2->agacharse();
		}else if(estadoTeclado[SDL_SCANCODE_C]){
			personaje2->piniaAlta();
		}else if(estadoTeclado[SDL_SCANCODE_V]){
			personaje2->patadaAlta();
		}else if(estadoTeclado[SDL_SCANCODE_B]){
			personaje2->deslizar();
			//personaje2->piniaBaja();
		}else if(estadoTeclado[SDL_SCANCODE_N]){
			personaje2->patadaBaja();
		}else if(estadoTeclado[SDL_SCANCODE_M]){
			personaje2->defender();
		}else{
			personaje2->mantenerReposo();
		}
    }
    if(estadoTeclado[SDL_SCANCODE_X]){
		personaje2->arrojarArma();
    }
}

void ControladorPersonaje::continuarAccionPreviaPersonaje1(){
    if (! personaje1->estaEnReposo())
        return;
    if(tipoDeControl == "TECLADO"){
    	identificarOrdenPersonaje1();
    }
}

void ControladorPersonaje::continuarAccionPreviaPersonaje2(){
    if (! personaje2->estaEnReposo())
        return;
    if(tipoDeControl == "TECLADO"){
    	identificarOrdenPersonaje2();
    }
}

ControladorPersonaje::~ControladorPersonaje() {
	ControladorJoystick::Instance()->clean();
	SDL_JoystickClose(joysticks[personaje1]);
	SDL_JoystickClose(joysticks[personaje2]);
}
