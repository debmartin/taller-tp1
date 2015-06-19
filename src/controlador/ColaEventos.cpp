/*
 * ColaEventos.cpp
 *
 *  Created on: 18/6/2015
 *      Author: gaston
 */

#include "ColaEventos.h"

ColaEventos::ColaEventos() {
	this->posPrimerEvento = 0;
	this->capacidad = 5;
	this->eventos = new deque<Evento*>;
}

ColaEventos::ColaEventos(size_t capacidad) {
	this->posPrimerEvento = 0;
	this->capacidad = capacidad;
	this->eventos = new deque<Evento*>;
}

ColaEventos::~ColaEventos() {
	this->eventos->clear();
}

void ColaEventos::agregarEvento(string nombreEvento) {

	if (this->posPrimerEvento > 0)
		this->posPrimerEvento--;

	if (this->eventos->size() >= this->capacidad)
		this->eventos->pop_front();

	this->eventos->push_back(new Evento(nombreEvento));
}

void ColaEventos::clear() {
	this->eventos->clear();
}

size_t ColaEventos::size() {
	return this->eventos->size();
}

std::deque<Evento*>::iterator ColaEventos::begin() {
	return this->eventos->begin();
}

std::deque<Evento*>::iterator ColaEventos::end() {
	return this->eventos->end();
}

bool ColaEventos::buscarCombo(Combo* c, size_t tolerancia) {

	// TECLAS DE COMBO
	vector<string>* teclasCombo = c->verTeclas();

	// INICIO COMPARACION
	bool comboEncontrado = compararConCombo(*teclasCombo, tolerancia);

	if (comboEncontrado) {
		//this->eventos->clear();
		return true;
	}

	return false;
}

bool ColaEventos::compararConCombo(vector<string> combo, size_t tolerancia) {

	vector<int> v_colorear;

	size_t indiceCombo = 0;
	size_t coincidencias = 0;
	size_t discrepancias = 0;

	for (size_t k = this->posPrimerEvento; k < this->eventos->size(); k++) {
		if ((*this->eventos)[k]->getNombre() == combo[0]) {

			v_colorear.clear();
			indiceCombo = 0;
			coincidencias = 0;
			discrepancias = 0;

			for (size_t j = k; j < this->eventos->size(); j++) {
				if ((*this->eventos)[j]->getNombre() == combo[indiceCombo]) {
					coincidencias++;
					indiceCombo++;

					v_colorear.push_back(j);

					if (coincidencias == combo.size()) {

						for (size_t m = 0; m < v_colorear.size(); m++)
							(*this->eventos)[v_colorear[m]]->colorear();

						this->posPrimerEvento = j + 1;
						return true;
					}
				}
				else {
					discrepancias++;
					if (discrepancias > tolerancia)
						break;
				}
			}
		}
	}

	return false;
}
