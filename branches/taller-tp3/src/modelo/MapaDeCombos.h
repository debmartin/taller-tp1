/*
 * MapaDeCombos.h
 *
 *  Created on: 1/6/2015
 *      Author: val
 */

#ifndef SRC_MODELO_MAPADECOMBOS_H_
#define SRC_MODELO_MAPADECOMBOS_H_

#include <SDL2/SDL.h>
#include <deque>
#include <string>
#include <vector>

#include "Combo.h"

#define LONGITUD_BUFFER 5
#define TIEMPO_MAXIMO_EN_COLA 5000 // milisegundos
using namespace std;

class MapaDeCombos {
private:
	vector<Combo*>* combosJugador;
	int toleranciaDeError;
	deque<string>* colaDeTeclas;
	string comboActual;
	bool comboEfectuado;
	void quitar_tecla();

	Uint32 tiempo_inicio_combo;

public:
	MapaDeCombos(vector<Combo*>* combosJugador, int toleranciaDeError);
	virtual ~MapaDeCombos();
	void agregar_tecla(string tecla);
	bool combo_completado();
	string informar_combo();
	void buscarCombo();
	deque<string>* getColaDeTeclas();

	void update();

    void imprimir();
};

#endif /* SRC_MODELO_MAPADECOMBOS_H_ */
