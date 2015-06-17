/*
 * Efecto.h
 *
 *  Created on: 19/6/2015
 *      Author: val
 */

#ifndef SRC_VISTA_EFECTO_H_
#define SRC_VISTA_EFECTO_H_

#include <iostream>
#include "../modelo/Vector2f.h"

class Efecto {
public:
	Efecto();
	virtual ~Efecto();
    virtual void dibujar() = 0;
    virtual void update() = 0;
    virtual void posicionar(Vector2f posicion) = 0;
    virtual void ejecutarEfecto(Vector2f pos) = 0;
};

#endif /* SRC_VISTA_EFECTO_H_ */
