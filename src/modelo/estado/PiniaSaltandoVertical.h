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
		PiniaSaltandoVertical(Vector2f posInicial, BVH* caja);
        virtual ~PiniaSaltandoVertical();
        bool estaSaltando();
};

#endif /* SRC_MODELO_ESTADO_PINIASALTANDOVERTICAL_H_ */
