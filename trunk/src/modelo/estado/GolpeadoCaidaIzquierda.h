/*
 * GolpeadoCaidaIzquierda.h
 *
 *  Created on: 24/5/2015
 *      Author: val
 */

#ifndef SRC_MODELO_ESTADO_GOLPEADOCAIDAIZQUIERDA_H_
#define SRC_MODELO_ESTADO_GOLPEADOCAIDAIZQUIERDA_H_

#include "Estado.h"

class GolpeadoCaidaIzquierda : public Estado
{
    public:
		GolpeadoCaidaIzquierda(Vector2f posInicial, BVH* caja);
        virtual ~GolpeadoCaidaIzquierda();
        bool estaSaltando();
        bool estaSaltandoDiagonalIzquierda();
    protected:
    private:
};

#endif /* SRC_MODELO_ESTADO_GOLPEADOCAIDAIZQUIERDA_H_ */
