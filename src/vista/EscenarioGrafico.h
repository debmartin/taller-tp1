/*
 * EscenarioGrafico.h
 *
 *  Created on: 24/3/2015
 *      Author: gaston
 */

#ifndef SRC_VISTA_ESCENARIOGRAFICO_H_
#define SRC_VISTA_ESCENARIOGRAFICO_H_

class EscenarioGrafico {
private:
	Sprite* personaje1;
	Sprite* personaje2;
	Sprite* capa1;
	Sprite* capa2;
	Sprite* capa3;

public:
	EscenarioGrafico();
	virtual ~EscenarioGrafico();
};

#endif /* SRC_VISTA_ESCENARIOGRAFICO_H_ */
