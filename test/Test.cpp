/*
 * Test.cpp
 *
 *  Created on: Mar 24, 2015
 *      Author: ariel
 */

#include "Test.h"

#include "LoggerTest.h"
#include "parser/ParserTests.h"

Test::Test() {
	// TODO Auto-generated constructor stub

}

void Test::ejecutar() {

	//ParserTests parserTests;
	//parserTests.ejecutar();

	LoggerTest loggerTest;
	loggerTest.ejecutar();

}

Test::~Test() {
	// TODO Auto-generated destructor stub
}

