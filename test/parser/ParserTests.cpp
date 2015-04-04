/*
 * ParserTests.cpp
 *
 *  Created on: Mar 24, 2015
 *      Author: ariel
 */

#include "ParserTests.h"

#include <iostream>
#include <list>

#include "../../src/modelo/Capa.h"
#include "../../src/modelo/Escenario.h"
#include "../../src/modelo/Personaje.h"
#include "../../src/modelo/Ventana.h"
#include "../../src/utils/Logger.h"

using namespace std;

#include "../../src/json/Parser.h"

ParserTests::ParserTests() {
	// TODO Auto-generated constructor stub

}

bool ParserTests::ejecutar() {

	Parser* parser = new Parser("src/recursos/escenario.json");

	parser->parsearDesdeJson();

	Ventana* ventana = parser->getVentana();
	cout<<*ventana<<endl;

	Escenario* escenario = parser->getEscenario();
	cout<<*escenario<<endl;

	for (list<Capa*>::iterator it_capas = parser->getCapas()->begin() ; it_capas != parser->getCapas()->end(); it_capas++)
	{
		cout<<**it_capas<<endl;
	}

	Personaje* personaje = parser->getPersonaje();
	cout<<*personaje<<endl;

	return true;
}

ParserTests::~ParserTests() {
	// TODO Auto-generated destructor stub
}

