/*
 * Pantalla.h
 *
 *  Created on: 30/5/2015
 *      Author: ariel
 */

#ifndef SRC_MENUS_PANTALLA_H_
#define SRC_MENUS_PANTALLA_H_

#include <string>

#define JUEGO_MODO_P1_VS_P2  "modo_p1_vs_p2"
#define JUEGO_MODO_P1_VS_CPU "modo_p1_vs_cpu"
#define JUEGO_MODO_PRACTICA  "modo_practica"

using namespace std;

class Pantalla {
protected:
	string tipoDeControl_jugador1;
	string tipoDeControl_jugador2;
public:
	Pantalla();
	Pantalla(string tipoDeControl_jugador1, string tipoDeControl_jugador2);
	virtual ~Pantalla();
	virtual void iniciar() = 0;
	string getTipoDeControlJugador1() const;
	string getTipoDeControlJugador2() const;
};

#endif /* SRC_MENUS_PANTALLA_H_ */
