/*
 * PiniaSaltandoDiagonalDerecha.h
 *
 *  Created on: 13/5/2015
 *      Author: val
 */

#ifndef SRC_MODELO_ESTADO_PINIASALTANDODIAGONALDERECHA_H_
#define SRC_MODELO_ESTADO_PINIASALTANDODIAGONALDERECHA_H_

#include "Estado.h"

class PiniaSaltandoDiagonalDerecha: public Estado
{
    public:
		PiniaSaltandoDiagonalDerecha(Vector2f posInicial, BVH* caja);
        virtual ~PiniaSaltandoDiagonalDerecha();
        bool estaSaltando();
};

#endif /* SRC_MODELO_ESTADO_PINIASALTANDODIAGONALDERECHA_H_ */
