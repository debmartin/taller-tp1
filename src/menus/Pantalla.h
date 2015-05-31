/*
 * Pantalla.h
 *
 *  Created on: 30/5/2015
 *      Author: ariel
 */

#ifndef SRC_MENUS_PANTALLA_H_
#define SRC_MENUS_PANTALLA_H_

#define JUEGO_MODO_P1_VS_P2  "modo_p1_vs_p2"
#define JUEGO_MODO_P1_VS_CPU "modo_p1_vs_cpu"
#define JUEGO_MODO_PRACTICA  "modo_practica"

class Pantalla {
public:
	Pantalla();
	virtual ~Pantalla();
	virtual void iniciar() = 0;
};

#endif /* SRC_MENUS_PANTALLA_H_ */
