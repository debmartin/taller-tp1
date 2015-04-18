/*
 * Test.cpp
 *
 *  Created on: Mar 24, 2015
 *      Author: ariel
 */

#include "Test.h"

#include "../src/utils/Logger.h"
#include "LoggerTest.h"
#include "parser/ParserTests.h"

Test::Test() {
	// TODO Auto-generated constructor stub

}

void Test::ejecutar() {

	Logger::getInstance()->info("#### INICIA LOS TEST ####");

	ParserTests parserTests;
	parserTests.ejecutar();

	LoggerTest loggerTest;
	loggerTest.ejecutar();

	Logger::getInstance()->info("#### TERMINA LOS TEST ####");
}

Test::~Test() {
	// TODO Auto-generated destructor stub
}

