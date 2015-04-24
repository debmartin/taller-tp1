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
	EscenarioGrafico* escenarioG;

	Personaje* jugador1;
	PersonajeDibujable* jugadorDibujable1;

	list<Personaje*>* personajes;
	list<PersonajeDibujable*>* personajesDibujables;
	list<Controlador*>* controladoresJuego;

public:
	Juego(EscenarioGrafico* escenario, Personaje* pers, PersonajeDibujable* persDib);
	void render();
	void update();
	void handleEvents(bool& recargar);
	bool running();
	void agregarPersonajes(list<Personaje*>* personajes, list<PersonajeDibujable*>* personajesDibujables);
	~Juego();

	//
	static Juego* Instance();
	list<Controlador*>* getControladoresJuego() const;

private:
	void definirControladores(list<Personaje*>* personajes);
};

typedef Juego ElJuego;

#endif /* SRC_JUEGO_H_ */
