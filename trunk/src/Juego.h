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
#include "vista/EscenarioGrafico.h"

using namespace std;

class Juego {
private:
	bool juegoCorriendo;
	Controlador* controladorJuego;

	Personaje* jugador1;
	Personaje* jugador2;
	PersonajeDibujable* jugadorDibujable1;
	PersonajeDibujable* jugadorDibujable2;

public:
	Juego();
	Juego(Personaje* pers, PersonajeDibujable* persDib);
	void render();
	void update();
	void handleEvents(bool& recargar);
	bool running();
	void agregarJugador1(Personaje* unPersonaje, PersonajeDibujable* unPersonajeDibujable);
	void agregarJugador2(Personaje* unPersonaje, PersonajeDibujable* unPersonajeDibujable);
	~Juego();

	//
	static Juego* Instance();

};

typedef Juego ElJuego;

#endif /* SRC_JUEGO_H_ */
