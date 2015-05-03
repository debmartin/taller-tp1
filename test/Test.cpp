/*
 * Test.cpp
 *
 *  Created on: Mar 24, 2015
 *      Author: ariel
 */

#include "Test.h"

#include "../src/modelo/Vector2f.h"
#include "../src/utils/Logger.h"
#include "../src/vista/Animacion.h"
#include "../src/vista/Renderizador.h"
#include "../src/vista/Sprite.h"
#include "LoggerTest.h"
#include "parser/ParserTests.h"

Test::Test() {
	// TODO Auto-generated constructor stub

}

void Test::ejecutar() {

	ParserTests parserTests;
	parserTests.ejecutar();

	LoggerTest loggerTest;
	loggerTest.ejecutar();

	Animacion* animacion1 = new Animacion();
	Animacion* animacion2 = new Animacion("imagen", 10, 20, "animacion_1", Renderizador::Instance()->getRenderer());

	Sprite* sprite1 = new Sprite();
	Vector2f posicion(2,3);
	Sprite* sprite2 = new Sprite(animacion2, posicion, ORIENTACION_IZQUIERDA);
	Logger::getInstance()->error(sprite2);
}

Test::~Test() {
	// TODO Auto-generated destructor stub
}

