/******************************************************************************
 *                   Algoritmos y Programación II - 75.41                     *
 *                        Cátedra Ing. Patricia Calvo                         *
 *            Facultad de Ingeniería - Universidad de Buenos Aires            *
 ******************************************************************************/

/**
* Cola
* Implementacion con tipo de dato fijo (definido en NodoSimplementeEnlazado.h).
* v0.1
* Autor: Mariano Simone (marianosimone+7541@gmail.com)
**/
#ifndef COLA_H_
#define COLA_H_

#include "NodoSimplementeEnlazado.h"

class Cola {
private:
    NodoSimplementeEnlazado* frente;
    NodoSimplementeEnlazado* ultimo;
    
public:
    Cola();
    ~Cola();

    /**
     * Agrega el elemento a la cola
     */
    void push(const Dato& dato);

    /**
     * Retorna el primer dato ingresado, y lo elimina de la cola
     */
    Dato pop();

    /**
     * Retorna el primer dato ingresado
     */
    Dato top();

    bool estaVacia();
};

#endif
