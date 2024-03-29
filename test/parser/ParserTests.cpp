/*
 * ParserTests.cpp
 *
 *  Created on: Mar 24, 2015
 *      Author: ariel
 */

#include "ParserTests.h"

#include <iostream>
#include <list>

#include "../../src/json/CapaDef.h"
#include "../../src/json/EscenarioDef.h"
#include "../../src/json/PersonajeDef.h"
#include "../../src/json/VentanaDef.h"
#include "../../src/utils/Logger.h"

using namespace std;

#include "../../src/json/Parser.h"

ParserTests::ParserTests() {
	// TODO Auto-generated constructor stub

}

bool ParserTests::ejecutar() {

	string nombre_escenario("src/recursos/escenario.json");

	Parser* parser = new Parser(nombre_escenario.c_str());

	parser->parsearDesdeJson();

	VentanaDef* ventana = parser->getVentanaDef();
	Logger::getInstance()->info(ventana);

	EscenarioDef* escenario = parser->getEscenarioDef();
	Logger::getInstance()->info(escenario);

	for (list<CapaDef*>::iterator it_capas = parser->getCapasDef()->begin() ; it_capas != parser->getCapasDef()->end(); it_capas++)
	{
		Logger::getInstance()->info(*it_capas);
	}

	for (list<PersonajeDef*>::iterator it_personajesDef = parser->getPersonajesDef()->begin() ; it_personajesDef != parser->getPersonajesDef()->end(); it_personajesDef++)
	{
		Logger::getInstance()->info(*it_personajesDef);
	}

	return true;
}

ParserTests::~ParserTests() {
	// TODO Auto-generated destructor stub
}

