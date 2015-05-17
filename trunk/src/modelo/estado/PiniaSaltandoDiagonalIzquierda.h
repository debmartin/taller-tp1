/*
 * PiniaSaltandoDiagonalIzquierda.h
 *
 *  Created on: 13/5/2015
 *      Author: val
 */

#ifndef SRC_MODELO_ESTADO_PINIASALTANDODIAGONALIZQUIERDA_H_
#define SRC_MODELO_ESTADO_PINIASALTANDODIAGONALIZQUIERDA_H_

#include "Estado.h"

class PiniaSaltandoDiagonalIzquierda: public Estado
{
    public:
		PiniaSaltandoDiagonalIzquierda(Vector2f posInicial, BVH* caja);
        virtual ~PiniaSaltandoDiagonalIzquierda();
        bool estaAtacando();
        bool estaSaltando();
        bool estaSaltandoDiagonal();
};

#endif /* SRC_MODELO_ESTADO_PINIASALTANDODIAGONALIZQUIERDA_H_ */
