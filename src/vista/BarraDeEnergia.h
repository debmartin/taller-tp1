/*
 * BarraDeEnergia.h
 *
 *  Created on: 27/4/2015
 *      Author: val
 */

#ifndef SRC_VISTA_BARRADEENERGIA_H_
#define SRC_VISTA_BARRADEENERGIA_H_

#include <SDL2/SDL.h>
#include <string>

using namespace std;

class BarraDeEnergia {
public:
	BarraDeEnergia(string nombre_personaje);
	virtual ~BarraDeEnergia();
	SDL_Surface* getSurface();

private:
	SDL_Surface barraDeEnergia;
	string nombre_personaje;
	int energia;
	int puntaje;
};

#endif /* SRC_VISTA_BARRADEENERGIA_H_ */
