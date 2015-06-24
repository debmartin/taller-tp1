/*
 * Juego.h
 *
 *  Created on: 27/3/2015
 *      Author: val
 */

#ifndef SRC_JUEGO_H_
#define SRC_JUEGO_H_
class Jugador;

class HUD;

class ControladorPersonaje;

#include <string>
#include "vista/EfectosEspeciales.h"

using namespace std;

class Juego {
private:
	bool juegoCorriendo;
	bool ejecutandoFinal;
	bool ejecutandoFatality;
	Jugador* jugador1;
	Jugador* jugador2;
	string modo_juego;
	ControladorPersonaje* controladorPersonaje;

public:
	Juego(Jugador* jugador1, Jugador* jugador2, string modo, string nombrePersonaje1, string nombrePersonaje2);
	void render();
	void update(bool& recargar);
	void handleEvents(bool& recargar, bool menu);
	bool running();
	void finalizarRound(bool& recargar);

	~Juego();
	//
	static Juego* Instance();

private:
	void actualizarOrientacionJugadores();
	void agregarObservadoresJugador(Jugador* unJugador);
	void posicionarPersonajes_enEjeX();

};

typedef Juego ElJuego;

#endif /* SRC_JUEGO_H_ */
