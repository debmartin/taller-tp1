/*
 * SaltandoOblicuoIzquierda.h
 *
 *  Created on: 24/5/2015
 *      Author: val
 */

#ifndef SRC_MODELO_ESTADO_SALTANDOOBLICUOIZQUIERDA_H_
#define SRC_MODELO_ESTADO_SALTANDOOBLICUOIZQUIERDA_H_

#include "Estado.h"

class SaltandoOblicuoIzquierda : public Estado
{
    public:
        SaltandoOblicuoIzquierda(Vector2f posInicial, BVH* caja);
        virtual ~SaltandoOblicuoIzquierda();
        bool estaSaltando();
        bool estaSaltandoDiagonalIzquierda();
    protected:
    private:
};

#endif /* SRC_MODELO_ESTADO_SALTANDOOBLICUOIZQUIERDA_H_ */
