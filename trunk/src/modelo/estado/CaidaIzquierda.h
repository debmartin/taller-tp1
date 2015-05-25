/*
 * CaidaIzquierda.h
 *
 *  Created on: 28/5/2015
 *      Author: val
 */

#ifndef SRC_MODELO_ESTADO_CAIDAIZQUIERDA_H_
#define SRC_MODELO_ESTADO_CAIDAIZQUIERDA_H_

#include "Estado.h"

class CaidaIzquierda : public Estado
{
    public:
		CaidaIzquierda(Vector2f posInicial, BVH* caja);
		CaidaIzquierda(Vector2f posInicial, estado_personaje estado , BVH* caja);
        virtual ~CaidaIzquierda();
        bool estaSaltando();
        bool estaSaltandoDiagonalIzquierda();
    protected:
    private:
};

#endif /* SRC_MODELO_ESTADO_CAIDAIZQUIERDA_H_ */
