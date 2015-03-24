/*
 * Parser.h
 *
 *  Created on: 24/3/2015
 *      Author: ariel
 */

#ifndef SRC_JSON_PARSER_H_
#define SRC_JSON_PARSER_H_
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <jsoncpp/json/json.h>
using namespace std;

struct capa{
	string imagen_fondo;
	float ancho;
};

class Parser {
private:
	Json::Value root;
	Json::Reader reader;
	bool bienParseado;
	string entrada;

	int ventana_anchopx;
	int ventana_altopx;
	int ventana_ancho;

	float escenario_ancho;
	float escenario_alto;
	int escenario_ypiso;

	vector <capa> capas;

	int personaje_ancho;
	int personaje_alto;
	int personaje_zindex;
	vector<string> personaje_sprites;

public:
	Parser();
	void inicializar();
	bool ejecutar();

	virtual ~Parser();
	bool isBienParseado() const;
	const vector<capa>& getCapas() const;
	float getEscenarioAlto() const;
	float getEscenarioAncho() const;
	int getPersonajeAlto() const;
	int getPersonajeAncho() const;
	const vector<string>& getPersonajeSprites() const;
	int getPersonajeZindex() const;
	const Json::Reader& getReader() const;
	const Json::Value& getRoot() const;
	int getVentanaAltopx() const;
	int getVentanaAncho() const;
	int getVentanaAnchopx() const;
	int getEscenarioYpiso() const;
	const string& getEntrada() const;
	void setEntrada(const string& entrada);
};

#endif /* SRC_JSON_PARSER_H_ */
