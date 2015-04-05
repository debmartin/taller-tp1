/*
 * Observador.h
 *
 *  Created on: 5/4/2015
 *      Author: val
 */

#ifndef SRC_VISTA_OBSERVADOR_H_
#define SRC_VISTA_OBSERVADOR_H_

class Observador{
    public:
        Observador();
        virtual ~Observador();
        virtual void actualizar() = 0;
};

#endif /* SRC_VISTA_OBSERVADOR_H_ */
