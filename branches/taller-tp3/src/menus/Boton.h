/*
 * Boton.h
 *
 *  Created on: 16/5/2015
 *      Author: ariel
 */

#ifndef SRC_BOTON_H_
#define SRC_BOTON_H_

#include <string>

class Posicion;
class Textura;

using namespace std;
#include<iostream>

#include <SDL2/SDL_rect.h>

union SDL_Event;

//The mouse button
class Boton{

private:
	Posicion* posicionModelo;
	string idContenido;
	SDL_Rect rectOrigen;
	SDL_Rect rectDestino;
	bool elegido;

public:

	Boton(Posicion* posicionModelo, string idContenido, SDL_Rect rectOrigen, SDL_Rect rectDestino);
	void render(Textura* textura);
	Posicion* getPosicionModelo() const;
	string getIdContenido() const;
	virtual ~Boton();
	SDL_Rect getRectDestino() const;
};

#endif /* SRC_BOTON_H_ */
