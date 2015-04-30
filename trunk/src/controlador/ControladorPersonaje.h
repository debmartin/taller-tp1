/*
 * ControladorPersonaje.h
 *
 *  Created on: 25/4/2015
 *      Author: ariel
 */

#ifndef SRC_CONTROLADOR_CONTROLADORPERSONAJE_H_
#define SRC_CONTROLADOR_CONTROLADORPERSONAJE_H_

#include <SDL2/SDL_events.h>

class Personaje;

class ControladorPersonaje {
private:
	Personaje* personaje1;
	Personaje* personaje2;
	SDL_Event eventoGuardado;
public:
	ControladorPersonaje(Personaje* personaje1, Personaje* personaje2);
	virtual ~ControladorPersonaje();
	bool manejar_Evento(SDL_Event &evento);
	void continuarAccionPreviaPersonaje1();
	void continuarAccionPreviaPersonaje2();
private:
	void identificarOrdenPersonaje1();
	void identificarOrdenPersonaje2();
};

#endif /* SRC_CONTROLADOR_CONTROLADORPERSONAJE_H_ */
