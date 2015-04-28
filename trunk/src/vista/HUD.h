/*
 * HUD.h
 *
 *  Created on: 27/4/2015
 *      Author: val
 */

#ifndef SRC_VISTA_HUD_H_
#define SRC_VISTA_HUD_H_

#include <SDL2/SDL.h>
#include "../modelo/Vector2f.h"

#define POSICION_PORCENTUAL_BARRA1 Vector2f(10, 10)
#define POSICION_PORCENTUAL_BARRA2 Vector2f(60, 10)
#define DIMENSION_PORCENTUAL_BARRA Vector2f(30, 10)

class HUD {
public:
	HUD(string nombre_personaje1, string nombre_personaje2);
	virtual ~HUD();

private:
	SDL_Surface barraDeEnergia1;
	SDL_Surface barraDeEnergia2;
	Vector2f posicionPx;
	Vector2f dimensionPx;
};

#endif /* SRC_VISTA_HUD_H_ */
