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

#include "ColaEventos.h"
#include "Combo.h"

#define LONGITUD_BUFFER 5

enum OrientacionCombo {
	COMBO_IZQUIERDA,
	COMBO_DERECHA
} typedef OrientacionCombo;

using namespace std;

class MapaDeCombos {
private:
	vector<Combo*>* combosJugador;
	int toleranciaDeError;
	ColaEventos* colaDeEventos;

	Uint32 tiempo_inicio_combo;
	Uint32 tiempo_maximo_en_cola;

	OrientacionCombo orientacion;

	void espejarCombos();

public:
	MapaDeCombos(vector<Combo*>* combosJugador, int toleranciaDeError, Uint32 tiempo_maximo_en_cola = 5000);
	virtual ~MapaDeCombos();
	void agregar_tecla(string tecla);
	string informar_combo();
	ColaEventos* getColaDeEventos();
	void setOrientacion(OrientacionCombo nuevaOrientacion);
	void update();

    void imprimir();
};

#endif /* SRC_MODELO_MAPADECOMBOS_H_ */
