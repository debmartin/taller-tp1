/*
 * Gancho.h
 *
 *  Created on: 12/5/2015
 *      Author: val
 */

#ifndef SRC_MODELO_ESTADO_GANCHO_H_
#define SRC_MODELO_ESTADO_GANCHO_H_

#include "Estado.h"

class Gancho : public Estado
{
    public:
		Gancho(Vector2f posInicial, BVH* caja);
        virtual ~Gancho();
        bool estaAtacando();
        bool efectuandoGancho();
        bool ejecutandoMovimientoEspecial();
};

#endif /* SRC_MODELO_ESTADO_GANCHO_H_ */
