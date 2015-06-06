/*
 * Combo.h
 *
 *  Created on: 1/6/2015
 *      Author: val
 */

#ifndef SRC_MODELO_COMBO_H_
#define SRC_MODELO_COMBO_H_

#include <iostream>
#include <map>
#include <string>

using namespace std;

class Combo {
private:
	string nombreCombo;
	int numeroCombo;
	map<string, int>* mapaDeTeclas;
public:
	Combo(map<string, int>* mapaDeTeclas, string nombre, int numero);
	virtual ~Combo();
	string getNombre();
	int getNumero();
};

#endif /* SRC_MODELO_COMBO_H_ */
