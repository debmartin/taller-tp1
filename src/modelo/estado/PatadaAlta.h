/*
 * PatadaAlta.h
 *
 *  Created on: 17/5/2015
 *      Author: val
 */

#ifndef SRC_MODELO_ESTADO_PATADAALTA_H_
#define SRC_MODELO_ESTADO_PATADAALTA_H_

#include "Estado.h"

class PatadaAlta : public Estado
{
    public:
	PatadaAlta(Vector2f posInicial, BVH* caja);
        virtual ~PatadaAlta();
        bool estaAtacando();
        bool estaDefendiendo();
};

#endif /* SRC_MODELO_ESTADO_PATADAALTA_H_ */
