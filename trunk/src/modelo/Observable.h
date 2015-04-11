/*
 * Observable.h
 *
 *  Created on: 5/4/2015
 *      Author: val
 */

#ifndef SRC_MODELO_OBSERVABLE_H_
#define SRC_MODELO_OBSERVABLE_H_

#include "Observador.h"
#include <list>

class Observable{
    public:
        Observable();
        virtual ~Observable();
        void agregarObservador(Observador* unObservador);
        void notificarObservadores();
    private:
        std::list<Observador*>* observadores;
};

#endif /* SRC_MODELO_OBSERVABLE_H_ */
