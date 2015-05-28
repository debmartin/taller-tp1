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

using namespace std;

class Juego {
private:
	bool juegoCorriendo;
	bool ejecutandoFinal;
	Jugador* jugador1;
	Jugador* jugador2;
	ControladorPersonaje* controladorPersonaje;
	HUD* hud;

public:
	Juego(Jugador* jugador1, Jugador* jugador2);
	void render();
	void update(bool& recargar);
	void handleEvents(bool& recargar);
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
