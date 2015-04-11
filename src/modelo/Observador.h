/*
 * Observador.h
 *
 *  Created on: 7/4/2015
 *      Author: val
 */

#ifndef SRC_MODELO_OBSERVADOR_H_
#define SRC_MODELO_OBSERVADOR_H_

class Observable;

class Observador{
    public:
        Observador();
        virtual ~Observador();
        virtual void recibirNotificacion(Observable* unObservable) = 0;
};

#endif /* SRC_MODELO_OBSERVADOR_H_ */
