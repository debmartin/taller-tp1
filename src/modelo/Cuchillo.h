/*
 * Cuchillo.h
 *
 *  Created on: 28/4/2015
 *      Author: val
 */

#ifndef SRC_MODELO_CUCHILLO_H_
#define SRC_MODELO_CUCHILLO_H_

#include "Objeto.h"
#include "MRU.h"
#include <SDL2/SDL_timer.h>

#define DANIO_CUCHILLO	10

class Cuchillo: public Objeto {
private:
	int damage;
	Vector2f posicion;
	Trayectoria* trayectoria;
	float tCreacion;

public:
	Cuchillo();
	virtual ~Cuchillo();
	int quitarEnergia();
	void posicionar(Vector2f);
	void update();
};

#endif /* SRC_MODELO_CUCHILLO_H_ */
