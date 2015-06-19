/*
 * ControladorPersonaje.h
 *
 *  Created on: 25/4/2015
 *      Author: ariel
 */

#ifndef SRC_CONTROLADOR_CONTROLADORPERSONAJE_H_
#define SRC_CONTROLADOR_CONTROLADORPERSONAJE_H_

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_joystick.h>
#include <map>

#include "../modelo/Personaje.h"
#include "ControladorJoystick.h"
#include "MapaDeCombos.h"
#include "../vista/hud/HUD.h"

class Jugador;

class Personaje;

class ControladorPersonaje {
private:
	Personaje* personaje1;
	Personaje* personaje2;
	SDL_Event eventoGuardado;
	std::map<Personaje*, SDL_Joystick*> joysticks;
	string tipoDeControl;
	string modo_juego;
public:
	ControladorPersonaje(Jugador* juagador1, Jugador* jugador2, string tipoControl, string modo);
	virtual ~ControladorPersonaje();
	bool manejar_Evento(SDL_Event &evento);
	void continuarAccionPreviaPersonaje1();
	void continuarAccionPreviaPersonaje2();
private:
	void identificarOrdenJoystickPersonaje(Personaje* personaje, JoyNumber numeroJoystick);
	void identificarCombo(Personaje* personaje, JoyNumber numeroJoystick, Personaje* enemigo);
	void identificarOrdenPersonaje(Personaje* personaje);
	void identificarOrdenPersonaje1();
	void identificarOrdenPersonaje2();
};

#endif /* SRC_CONTROLADOR_CONTROLADORPERSONAJE_H_ */
