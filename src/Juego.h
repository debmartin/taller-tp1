/*
 * Juego.h
 *
 *  Created on: 27/3/2015
 *      Author: val
 */

#ifndef SRC_JUEGO_H_
#define SRC_JUEGO_H_

#include <utility>
#include "vista/hud/HUD.h"

class ControladorPersonaje;
class Personaje;
class PersonajeDibujable;

using namespace std;

class Juego {
private:
	bool juegoCorriendo;

	Personaje* jugador1;
	Personaje* jugador2;
	PersonajeDibujable* jugadorDibujable1;
	PersonajeDibujable* jugadorDibujable2;

	ControladorPersonaje* controladorPersonaje;
	HUD* hud;

    void agregarObservadoresJugador(Personaje* unPersonaje, PersonajeDibujable* unPersonajeDibujable);

public:
	Juego(std::pair<Personaje*, PersonajeDibujable*>& personaje1, std::pair<Personaje*, PersonajeDibujable*>& personaje2);
	void render();
	void update();
	void handleEvents(bool& recargar);
	bool running();
	~Juego();
	//
	static Juego* Instance();

private:
	void actualizarOrientacionJugadores();

};

typedef Juego ElJuego;

#endif /* SRC_JUEGO_H_ */
