/*
 * MapaDeCombos.h
 *
 *  Created on: 1/6/2015
 *      Author: val
 */

#ifndef SRC_MODELO_MAPADECOMBOS_H_
#define SRC_MODELO_MAPADECOMBOS_H_

#include <list>
#include "Combo.h"

using namespace std;

class MapaDeCombos {
private:
	list<Combo*>* combosJugador1;
	list<Combo*>* combosJugador2;
	int toleranciaDeError;

public:
	MapaDeCombos(list<Combo*>* combosJugador1, list<Combo*>* combosJugador2, int toleranciaDeError);
	virtual ~MapaDeCombos();
};

#endif /* SRC_MODELO_MAPADECOMBOS_H_ */
