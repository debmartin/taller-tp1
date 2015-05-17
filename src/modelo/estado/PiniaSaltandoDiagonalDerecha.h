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
		PiniaSaltandoDiagonalDerecha(Trayectoria* trayectoriaActual, float tiempoDeCreacion, BVH* caja);
        virtual ~PiniaSaltandoDiagonalDerecha();
        bool estaAtacando();
        bool estaSaltando();
        bool estaSaltandoDiagonalDerecha();
};

#endif /* SRC_MODELO_ESTADO_PINIASALTANDODIAGONALDERECHA_H_ */
