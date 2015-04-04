/*
 * Parser.h
 *
 *  Created on: 24/3/2015
 *      Author: ariel
 */

#ifndef SRC_JSON_PARSER_H_
#define SRC_JSON_PARSER_H_

#include <jsoncpp/json/json.h>
#include <list>
#include <string>

#include "../../src/modelo/Capa.h"
#include "../../src/modelo/Escenario.h"
#include "../../src/modelo/Personaje.h"
#include "../../src/modelo/Ventana.h"

using namespace std;

class Parser {
private:
	Json::Value root;
	Json::Reader reader;
	bool bienParseado;
	bool existe_archivo;
	string entrada;

	//objectos que devolvera el parseador json
	Ventana* ventana;
	Escenario * escenario;
	list<Capa*>* capas;
	Personaje* personaje;


public:
	Parser();
	Parser(string archivo_json);

	list<Capa*>* getCapas() const;
	Escenario* getEscenario() const;
	Personaje* getPersonaje() const;
	Ventana* getVentana() const;

	void parsearDesdeJson();

	virtual ~Parser();
	const Json::Reader& getReader() const;
	const Json::Value& getRoot() const;
	double getPersonajeSpritesAncho() const;
	void setPersonajeSpritesAncho(double personajeSpritesAncho);

private:
	void inicializar();
	void crearEscenerioPorDefecto();
	void inciarValidacionSemantica();

};

#endif /* SRC_JSON_PARSER_H_ */
