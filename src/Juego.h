/*
 * Juego.h
 *
 *  Created on: 27/3/2015
 *      Author: val
 */

#ifndef SRC_JUEGO_H_
#define SRC_JUEGO_H_

#include <vector>
#include <SDL2/SDL.h>
#include "vista/Sprite.h" // TODO: solo para test
#include "controlador/Controlador.h"
#include "vista/PersonajeDibujable.h"
#include <iostream>
#include <string>

using namespace std;

class Juego {
private:
	bool juegoCorriendo;
	Controlador controladorJuego;
	Personaje jugador1;
	PersonajeDibujable jugadorDibujable1;
	Sprite* subzero;
public:

	Juego(const char* titulo, int xpos, int ypos, int altura, int ancho, bool fullscreen);
	void render();
	void update();
	void handleEvents();
	void clean();
	bool running();
	~Juego();

	// create the public  instance function
	static Juego* Instance();
};

typedef Juego ElJuego;

#endif /* SRC_JUEGO_H_ */