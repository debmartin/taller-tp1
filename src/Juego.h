/*
 * Juego.h
 *
 *  Created on: 27/3/2015
 *      Author: val
 */

#ifndef SRC_JUEGO_H_
#define SRC_JUEGO_H_

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

public:
	Juego();
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
