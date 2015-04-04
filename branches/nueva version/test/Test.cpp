/*
 * Test.cpp
 *
 *  Created on: Mar 24, 2015
 *      Author: ariel
 */

#include "Test.h"
#include "parser/ParserTests.h"

Test::Test() {
	// TODO Auto-generated constructor stub

}

bool Test::ejecutar() {

	bool salida = true;
	ParserTests parserTests;
	salida = parserTests.ejecutar();

	return salida;
}

Test::~Test() {
	// TODO Auto-generated destructor stub
}

