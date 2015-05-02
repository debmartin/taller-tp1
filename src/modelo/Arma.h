/*
 * Arma.h
 *
 *  Created on: 2/5/2015
 *      Author: val
 */

#ifndef SRC_MODELO_ARMA_H_
#define SRC_MODELO_ARMA_H_

#include "Objeto.h"
#include "MRU.h"
#include <SDL2/SDL_timer.h>

#define DANIO_ARMA	10

class Arma: public Objeto {
private:
	int damage;
	Vector2f posicion;
	Trayectoria* trayectoria;
	float tCreacion;
public:
	Arma();
	virtual ~Arma();
	int quitarEnergia();
	void posicionar(Vector2f);
	void update();
};

#endif /* SRC_MODELO_ARMA_H_ */
