/*
 * MapaDeCombos.h
 *
 *  Created on: 1/6/2015
 *      Author: val
 */

#ifndef SRC_MODELO_MAPADECOMBOS_H_
#define SRC_MODELO_MAPADECOMBOS_H_

#include <deque>
#include <string>
#include <vector>

#include "Combo.h"

using namespace std;

class MapaDeCombos {
private:
	vector<Combo*>* combosJugador;
	int toleranciaDeError;
	deque<string>* colaDeTeclas;
	string comboActual;
	bool comboEfectuado;
	void quitar_tecla();

public:
	MapaDeCombos(vector<Combo*>* combosJugador, int toleranciaDeError);
	virtual ~MapaDeCombos();
	void agregar_tecla(string tecla);
	bool combo_completado();
	string informar_combo();
	void buscarCombo();
	deque<string>* getColaDeTeclas();

    void imprimir();
};

#endif /* SRC_MODELO_MAPADECOMBOS_H_ */
