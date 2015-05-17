/*
 * PatadaBaja.h
 *
 *  Created on: 17/5/2015
 *      Author: val
 */

#ifndef SRC_MODELO_ESTADO_PATADABAJA_H_
#define SRC_MODELO_ESTADO_PATADABAJA_H_

#include "Estado.h"

class PatadaBaja : public Estado
{
    public:
	PatadaBaja(Vector2f posInicial, BVH* caja);
        virtual ~PatadaBaja();
        bool estaAtacando();
        bool estaDefendiendo();
        bool estaBloqueado();
};


#endif /* SRC_MODELO_ESTADO_PATADABAJA_H_ */
