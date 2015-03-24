/*
 * ParserTests.cpp
 *
 *  Created on: Mar 24, 2015
 *      Author: ariel
 */

#include "ParserTests.h"

#include <iostream>
#include <string>
#include <vector>

#include "../../src/modelo/Capa.h"
#include "../../src/modelo/Escenario.h"
#include "../../src/modelo/Personaje.h"
#include "../../src/modelo/Ventana.h"

using namespace std;

#include "../../src/json/Parser.h"

ParserTests::ParserTests() {
	// TODO Auto-generated constructor stub

}

bool ParserTests::ejecutar() {

	cout<<"Iniciar test del parser(jsoncpp) ..."<<endl;

	string entrada = "src/recursos/escenario2.json";
	Parser parser;
	parser.setEntrada("src/recursos/escenario2.json");
	parser.inicializar();

	bool construirObjetos = parser.ejecutar();

	if ( construirObjetos )
	{
		Ventana ventana;
		ventana.setAnchoPx(parser.getVentanaAnchopx());
		ventana.setAltoPx(parser.getVentanaAltopx());
		ventana.setAncho(parser.getVentanaAncho());

		Escenario escenario;
		escenario.setAncho(parser.getEscenarioAncho());
		escenario.setAlto(parser.getEscenarioAlto());
		escenario.setYpiso(parser.getEscenarioYpiso());

		Capa capa1;
		capa1.setImagenFondo("fondo1.png");
		capa1.setAncho(500);

		Capa capa2;
		capa2.setImagenFondo("fondo2.png");
		capa2.setAncho(1000.5);

		Personaje personaje;
		personaje.setAncho(parser.getPersonajeAncho());
		personaje.setAlto(parser.getPersonajeAlto());
		personaje.setZindex(parser.getPersonajeZindex());

		vector<string> sprites;
		sprites.push_back("sprites_1");
		sprites.push_back("sprites_2");
		sprites.push_back("sprites_3");

		personaje.setSprites(sprites);
	}

	return true;
}

ParserTests::~ParserTests() {
	// TODO Auto-generated destructor stub
}

