/*
 * Controlador.h
 *
 *  Created on: 23/3/2015
 *      Author: val
 */

#ifndef SRC_CONTROLADOR_CONTROLADOR_H_
#define SRC_CONTROLADOR_CONTROLADOR_H_

#include "../modelo/Personaje.h"
#include "../vista/PersonajeDibujable.h"
#include <SDL2/SDL.h>

using namespace std;

class Controlador {
private:
	Personaje* unPersonaje;

public:
	Controlador(Personaje* pers);
	virtual ~Controlador();
	bool manejar_Evento(SDL_Event &evento);
	void setPersonaje(Personaje* personaje);
};

#endif /* SRC_CONTROLADOR_CONTROLADOR_H_ */