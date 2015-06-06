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
	map<string, char> mapaDeLetras;
	queue<char> colaDeEventos;
	Combo* comboActual;

	void pasar_a_string(Combo* combo);

public:
	MapaDeCombos(list<Combo*>* combosJugador1, list<Combo*>* combosJugador2, int toleranciaDeError);
	virtual ~MapaDeCombos();
	void agregar_evento(string tecla);
	bool combo_completado();
	int informar_combo();
};

#endif /* SRC_MODELO_MAPADECOMBOS_H_ */
