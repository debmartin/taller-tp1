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
	list<Combo*>* combosJugador;
	int toleranciaDeError;
	queue<string>* colaDeTeclas;
	Combo* comboActual;

	void quitar_tecla();

public:
	MapaDeCombos(list<Combo*>* combosJugador, int toleranciaDeError);
	virtual ~MapaDeCombos();
	void agregar_tecla(string tecla);
	bool combo_completado();
	int informar_combo();
};

#endif /* SRC_MODELO_MAPADECOMBOS_H_ */
