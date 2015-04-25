/*
 * HSV.h
 *
 *  Created on: 25/4/2015
 *      Author: gaston
 */

#ifndef SRC_VISTA_HSV_H_
#define SRC_VISTA_HSV_H_
#include <SDL2/SDL.h>

#define GRADOS60 60
#define GRADOS120 120
#define GRADOS360 360
#define GRADOS0 0

class HSV {
public:
	HSV(SDL_Texture* s);
	// Esta funcion puede llegar a necesitar de Renderizador::Instance()->getWindow()
	// o puede ser pasado por parametro.
	void desplazarH(float hInicial, float hFinal, float desplazamiento);
	SDL_Texture* toTexture();
	virtual ~HSV();

private:
	float H;
	float S;
	float V;
	int max;
	int min;
	int maximo(int R, int G, int B);
	int minimo(int R, int G, int B);
	void setH(int R, int G, int B);
	void setS(int R, int G, int B);
	void setV(int R, int G, int B);
};

#endif /* SRC_VISTA_HSV_H_ */
