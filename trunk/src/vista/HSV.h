/*
 * HSV.h
 *
 *  Created on: 25/4/2015
 *      Author: gaston
 */

#ifndef SRC_VISTA_HSV_H_
#define SRC_VISTA_HSV_H_
#include <SDL2/SDL.h>

class HSV {
public:
	HSV(SDL_Texture* s);
	// Esta funcion puede llegar a necesitar de Renderizador::Instance()->getWindow()
	// o puede ser pasado por parametro.
	void desplazarH(float hInicial, float hFinal, float desplazamiento);
	SDL_Texture* toTexture();
	virtual ~HSV();

private:
	float maximo(float R, float G, float V);
	float minimo(float R, float G, float V);
	float componenteH();
	float componenteS();
	float componenteV();
};

#endif /* SRC_VISTA_HSV_H_ */
