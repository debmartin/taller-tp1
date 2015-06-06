/*
 * MapaDeCombos.cpp
 *
 *  Created on: 1/6/2015
 *      Author: val
 */

#include "MapaDeCombos.h"

MapaDeCombos::MapaDeCombos(list<Combo*>* lista1, list<Combo*>* lista2, int tolerancia):
	combosJugador1(lista1), combosJugador2(lista2), toleranciaDeError(tolerancia){
	comboActual = NULL;


	for (list<Combo*>::iterator iterador1 = lista1->begin(); iterador1 != lista1->end(); ++iterador1) {
		pasar_a_string((*iterador1));
	}

	for (list<Combo*>::iterator iterador2 = lista2->begin(); iterador2 != lista2->end(); ++iterador2) {
		pasar_a_string((*iterador2));
	}
}

/*Arma un string con la secuencia de letras que forman el combo*/
void MapaDeCombos::pasar_a_string(Combo* combo){

}

void MapaDeCombos::agregar_evento(string tecla){
	this->colaDeEventos.push(this->mapaDeLetras[tecla]);
}

bool MapaDeCombos::combo_completado(){
	return (comboActual != NULL);
}

int MapaDeCombos::informar_combo(){
	return comboActual->getNumero();
}

MapaDeCombos::~MapaDeCombos() {
	// TODO Auto-generated destructor stub
}

