/*
 * Posicionable.h
 *
 *  Created on: 3/4/2015
 *      Author: val
 */

#ifndef SRC_VISTA_POSICIONABLE_H_
#define SRC_VISTA_POSICIONABLE_H_

#include "../modelo/Vector2f.h"

class Posicionable
{
    public:
        Posicionable();
        virtual ~Posicionable();
        virtual bool esValida(Vector2f posicion, double ancho) = 0;
        virtual bool enExtremos(float distanciaEntreElementos, double ancho) = 0;
};



#endif /* SRC_VISTA_POSICIONABLE_H_ */
