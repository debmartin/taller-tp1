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
	map<string, int>* mapaDeTeclas;
public:
	Combo(map<string, int>* mapaDeTeclas, string nombre);
	virtual ~Combo();
	string getNombre();
};

#endif /* SRC_MODELO_COMBO_H_ */
