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

typedef struct
{
	string imagen_fondo;
	double ancho;
} tCapa;

class Parser {
private:
	Json::Value root;
	Json::Reader reader;
	bool bienParseado;
	string entrada;

	int ventana_anchopx;
	int ventana_altopx;
	double ventana_ancho;

	double escenario_ancho;
	double escenario_alto;
	int escenario_ypiso;

	vector<tCapa> capas;

	double personaje_ancho;
	double personaje_alto;
	int personaje_zindex;
	string personaje_sprites_imagen;
	double personaje_sprites_ancho;

public:
	Parser();
	void inicializar();
	bool ejecutar();

	virtual ~Parser();
	vector<tCapa> getCapas();
	double getEscenarioAlto() const;
	double getEscenarioAncho() const;
	double getPersonajeAlto() const;
	double getPersonajeAncho() const;
	int getPersonajeZindex() const;
	const Json::Reader& getReader() const;
	const Json::Value& getRoot() const;
	int getVentanaAltopx() const;
	double getVentanaAncho() const;
	int getVentanaAnchopx() const;
	int getEscenarioYpiso() const;
	const string& getEntrada() const;
	void setEntrada(const string& entrada);
	double getPersonajeSpritesAncho() const;
	void setPersonajeSpritesAncho(double personajeSpritesAncho);
	const string& getPersonajeSpritesImagen() const;
	void setPersonajeSpritesImagen(const string& personajeSpritesImagen);
};

#endif /* SRC_JSON_PARSER_H_ */
