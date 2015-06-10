/*
 * Arrojado.h
 *
 *  Created on: 10/6/2015
 *      Author: val
 */

#ifndef SRC_MODELO_ESTADO_ARROJADO_H_
#define SRC_MODELO_ESTADO_ARROJADO_H_

#include "Estado.h"
#include "../MRU.h"

class Arrojado : public Estado
{
    public:
		Arrojado(Vector2f posInicial, estado_personaje estado, BVH* caja, bool direccion);
        virtual ~Arrojado();
    protected:
    private:
};
#endif /* SRC_MODELO_ESTADO_ARROJADO_H_ */
