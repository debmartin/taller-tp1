/*
 * Deslizar.h
 *
 *  Created on: 1/6/2015
 *      Author: val
 */

#ifndef SRC_MODELO_ESTADO_DESLIZAR_H_
#define SRC_MODELO_ESTADO_DESLIZAR_H_

#include "Estado.h"
#include "../MRU.h"

class Deslizar : public Estado
{
    public:
		Deslizar(Vector2f posInicial, BVH* caja, bool direccion);
        virtual ~Deslizar();
        bool estaAtacando();
    protected:
    private:
};

#endif /* SRC_MODELO_ESTADO_DESLIZAR_H_ */
