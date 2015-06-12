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

const int BUTTON_WIDTH = 90; // ancho original -> 118.20;
const int BUTTON_HEIGHT = 127;

//The mouse button
class Boton{

private:
	//Top left position
	SDL_Point mPosition;
	// poscion en la matriz de la botonera
	Posicion* posicionModelo;
	bool elegido;
	string idContenido;
	SDL_Rect dimension;

public:

	Boton(Posicion* posicionModelo, Posicion* posicionVista);

	//Shows button sprite
	void render(Textura* textura);

	virtual ~Boton();

	friend ostream& operator<<(ostream &o, const Boton &b);
	Posicion* getPosicionModelo() const;
	void cargarIdContenido(string idContenido);
	string getIdContenido() const;
	void cargarDimension(SDL_Rect dimension);
};

#endif /* SRC_BOTON_H_ */
