/*
 * Combo.h
 *
 *  Created on: 1/6/2015
 *      Author: val
 */

#ifndef SRC_MODELO_COMBO_H_
#define SRC_MODELO_COMBO_H_

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Combo {
private:
	string nombreCombo;
	int numeroCombo;
	vector<string>* teclas;
public:
	Combo(vector<string>* teclas, string nombre, int numero);
	virtual ~Combo();
	string getNombre();
	int getNumero();
	vector<string>* verTeclas();
};

#endif /* SRC_MODELO_COMBO_H_ */
