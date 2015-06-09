/*
 * MapaDeCombos.h
 *
 *  Created on: 1/6/2015
 *      Author: val
 */

#ifndef SRC_MODELO_MAPADECOMBOS_H_
#define SRC_MODELO_MAPADECOMBOS_H_

#include <SDL2/SDL_events.h>
#include <queue>
#include <list>
#include "Combo.h"

using namespace std;

class MapaDeCombos {
private:
	list<Combo*>* combosJugador1;
	list<Combo*>* combosJugador2;
	int toleranciaDeError;
	queue<string>* colaDeEventosPersonaje1;
	queue<string>* colaDeEventosPersonaje2;
	Combo* comboActual;

	void quitar_tecla(int numeroPersonaje);

public:
	MapaDeCombos(list<Combo*>* combosJugador1, list<Combo*>* combosJugador2, int toleranciaDeError);
	virtual ~MapaDeCombos();
	void agregar_tecla(string tecla, int personaje);
	bool combo_completado();
	int informar_combo();
};

#endif /* SRC_MODELO_MAPADECOMBOS_H_ */
