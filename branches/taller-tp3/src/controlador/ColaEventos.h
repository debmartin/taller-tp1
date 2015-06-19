/*
 * ColaEventos.h
 *
 *  Created on: 18/6/2015
 *      Author: gaston
 */

#ifndef SRC_CONTROLADOR_COLAEVENTOS_H_
#define SRC_CONTROLADOR_COLAEVENTOS_H_
#include <iostream>
#include <deque>
#include "Evento.h"
#include "Combo.h"

using namespace std;

class ColaEventos {

public:
	ColaEventos(size_t capacidad);
	void agregarEvento(string nombreEvento);
	bool buscarCombo(Combo* c, size_t tolerancia);
	void clear();
	size_t size();
	std::deque<Evento*>::iterator begin();
	std::deque<Evento*>::iterator end();
	virtual ~ColaEventos();

private:
	ColaEventos();
	size_t posPrimerEvento;
	size_t capacidad;
	deque<Evento*>* eventos;
	bool compararConCombo(vector<string> combo, size_t tolerancia);
};

#endif /* SRC_CONTROLADOR_COLAEVENTOS_H_ */
