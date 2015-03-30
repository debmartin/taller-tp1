/*
 * ParserTests.cpp
 *
 *  Created on: Mar 24, 2015
 *      Author: ariel
 */

#include "ParserTests.h"

#include <iostream>
#include <iterator>
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

	Parser parser;
	parser.setEntrada("src/recursos/escenario.json");
	parser.inicializar();

	bool construirObjetos = parser.ejecutar();

	if ( construirObjetos )
	{
		Ventana ventana;
		ventana.setAnchoPx(parser.getVentanaAnchopx());
		ventana.setAltoPx(parser.getVentanaAltopx());
		ventana.setAncho(parser.getVentanaAncho());
		//cout<<ventana<<endl;

		Escenario escenario;
		escenario.setAncho(parser.getEscenarioAncho());
		escenario.setAlto(parser.getEscenarioAlto());
		escenario.setYpiso(parser.getEscenarioYpiso());
		//cout<<escenario<<endl;

		//vector<Capa> capas;
		/*
		cout<<"se muestran las capas"<<endl;
		for (vector<tCapa*>::iterator it = parser.getCapas()->begin() ; it != parser.getCapas()->end(); ++it)
		{
			cout<<"capa: "<<(*it)->imagen_fondo<<", "<<(*it)->ancho<<endl;
		}*/

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
		personaje.setSpritesImagen(parser.getPersonajeSpritesImagen());
		personaje.setSpritesAncho(parser.getPersonajeSpritesAncho());
		//cout<<personaje<<endl;
	}

	return true;
}

ParserTests::~ParserTests() {
	// TODO Auto-generated destructor stub
}

