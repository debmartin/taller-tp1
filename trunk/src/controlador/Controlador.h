/*
 * Controlador.h
 *
 *  Created on: 23/3/2015
 *      Author: val
 */

#ifndef SRC_CONTROLADOR_CONTROLADOR_H_
#define SRC_CONTROLADOR_CONTROLADOR_H_

#include "../modelo/Personaje.h"
#include <SDL2/SDL.h>

using namespace std;

class Controlador {
private:
	Personaje unPersonaje;
public:
	Controlador();
	virtual ~Controlador();
	void manejar_Evento(SDL_Event &evento);

};

#endif /* SRC_CONTROLADOR_CONTROLADOR_H_ */
