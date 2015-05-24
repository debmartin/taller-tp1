/*
 * PiniaSaltandoVertical.h
 *
 *  Created on: 13/5/2015
 *      Author: val
 */

#ifndef SRC_MODELO_ESTADO_PINIASALTANDOVERTICAL_H_
#define SRC_MODELO_ESTADO_PINIASALTANDOVERTICAL_H_

#include "Estado.h"

class PiniaSaltandoVertical: public Estado
{
    public:
		PiniaSaltandoVertical(Trayectoria* trayectoriaActual, float tiempoCreacion, BVH* caja);
		PiniaSaltandoVertical(Vector2f posInicial, BVH* caja);
        virtual ~PiniaSaltandoVertical();
        bool estaAtacando();
        bool estaSaltando();
        bool estaSaltandoVertical();
};

#endif /* SRC_MODELO_ESTADO_PINIASALTANDOVERTICAL_H_ */
