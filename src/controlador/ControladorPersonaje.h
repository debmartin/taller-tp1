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
	Personaje* personaje1;
	Personaje* personaje2;
	SDL_Event eventoGuardado;
    void identificarOrden();
public:
	ControladorPersonaje();
	ControladorPersonaje(Personaje* pers);
	virtual ~ControladorPersonaje();
	bool manejar_Evento(SDL_Event &evento);
	void continuarAccionPrevia();
	void setPersonaje(Personaje* personaje);
	SDL_Event obtenerUltimoEvento();

	void agregarPersonaje1(Personaje* personaje1);
	void agregarPersonaje2(Personaje* personaje2);
};

#endif /* SRC_CONTROLADOR_CONTROLADORPERSONAJE_H_ */
