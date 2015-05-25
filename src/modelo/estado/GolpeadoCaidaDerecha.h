/*
 * GolpeadoCaidaDerecha.h
 *
 *  Created on: 24/5/2015
 *      Author: val
 */

#ifndef SRC_MODELO_ESTADO_GOLPEADOCAIDADERECHA_H_
#define SRC_MODELO_ESTADO_GOLPEADOCAIDADERECHA_H_

#include "Estado.h"

class GolpeadoCaidaDerecha : public Estado
{
    public:
		GolpeadoCaidaDerecha(Vector2f posInicial, BVH* caja);
        virtual ~GolpeadoCaidaDerecha();
        bool estaSaltando();
        bool estaSaltandoDiagonalDerecha();
    protected:
    private:
};

#endif /* SRC_MODELO_ESTADO_GOLPEADOCAIDADERECHA_H_ */
