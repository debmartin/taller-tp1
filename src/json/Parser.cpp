/*
 * Parser.cpp
 *
 *  Created on: 24/3/2015
 *      Author: ariel
 */

#include "Parser.h"

Parser::Parser() {
	// TODO Auto-generated constructor stub

}

void Parser::inicializar()
{
	ifstream archivo_escenario(this->entrada.c_str());
	this->bienParseado = this->reader.parse(archivo_escenario, this->root, false);

}

bool Parser::ejecutar() {

	 if( !this->bienParseado )
	 {
	   // Report failures and their locations in the document.
	   cout<<"Failed to parse JSON"<<endl
	       <<reader.getFormatedErrorMessages()
	       <<endl;
	   return false;
	 }

	 if( root.size() > 0 ) {
	 		for( Json::ValueIterator it = root.begin() ; it != root.end() ; it++ )
	 		{
	 			const Json::Value key_nivel1 = it.key();
	 			//tag padre es el tag que esta en el nivel de las deficiones
	 			string tag_padre = key_nivel1.asString();
	 			//cout<<"#"<<tag_padre<<endl;

	 			const Json::Value root2 = root[tag_padre];

	 			if ( root2.isArray() )
	 			{
	 				if ( tag_padre == "capas" )
	 				{
						for (unsigned int idx_capas = 0; idx_capas < root2.size(); ++idx_capas)
						{
							tCapa capa_actual;

							for( Json::ValueIterator it3 = root2[idx_capas].begin() ; it3 != root2[idx_capas].end() ; it3++ )
							{
								const Json::Value key_nivel2 = it3.key();
								if ( key_nivel2.asString() == "imagen_fondo" )
								{
									capa_actual.imagen_fondo = (*it)[idx_capas]["imagen_fondo"].asString();
								}
								else if ( key_nivel2.asString() == "ancho" )
								{
									capa_actual.ancho = (*it)[idx_capas]["ancho"].asDouble();
								}
								else
								{
									cout<<"parametro no encontrado!"<<endl;
								}
							}

							capas.push_back(capa_actual);
						}
	 				}
	 			}
	 			else
	 			{
					for( Json::ValueIterator it2 = root2.begin() ; it2 != root2.end() ; it2++ )
					{
						const Json::Value key_nivel2 = it2.key();

						if ( tag_padre == "ventana" )
						{
							if ( key_nivel2.asString() == "altopx" )
							{
								this->ventana_altopx = (*it)["altopx"].asInt();
							}
							else if ( key_nivel2.asString() == "ancho" )
							{
								this->ventana_ancho = (*it)["ancho"].asDouble();
							}
							else if ( key_nivel2.asString() == "anchopx" )
							{
								this->ventana_anchopx = (*it)["anchopx"].asInt();
							}
							else
							{
								cout<<"parametro no encontrado!"<<endl;
							}
						}
						else if ( tag_padre == "escenario" )
						{
							if ( key_nivel2.asString() == "alto" )
							{
								this->escenario_alto = (*it)["alto"].asDouble();
							}
							else if ( key_nivel2.asString() == "ancho" )
							{
								this->escenario_ancho = (*it)["ancho"].asDouble();
							}
							//TODO revisar porque este parametro tiene una longitud mas grande. mide 7 en vez de 5!
							else if ( key_nivel2.asString().compare("ypiso") >= 0 )
							{
								this->escenario_ypiso = (*it)[key_nivel2.asString()].asInt();
							}
							else
							{
								cout<<"parametro no encontrado!"<<endl;
							}
						}
						else if ( tag_padre == "personaje" )
						{
							if ( key_nivel2.asString() == "alto" )
							{
								this->personaje_alto = (*it)["alto"].asDouble();
							}
							else if ( key_nivel2.asString().compare("ancho") == 0 )
							{
								this->personaje_ancho = (*it)[key_nivel2.asString()].asDouble();
							}
							else if ( key_nivel2.asString().compare("zindex") >= 0 )
							{
								this->personaje_zindex = (*it)[key_nivel2.asString()].asInt();
							}
							else if ( key_nivel2.asString() == "sprites" )
							{
								this->personaje_sprites_imagen = (*it2)["imagen"].asString();
								this->personaje_sprites_ancho = (*it2)["ancho"].asDouble();
							}
							else
							{
								cout<<"parametro "<<key_nivel2.asString()<<" no encontrado!"<<endl;
							}
						}
						else
						{
							cout<<"Loggear la lectura de una tag invalido"<<endl;
						}
					}
	 			}
	 		}
	 	}

	 return true;
}

Parser::~Parser() {
	// TODO Auto-generated destructor stub
}

vector<tCapa> Parser::getCapas() {
	return capas;
}

double Parser::getEscenarioAlto() const {
	return escenario_alto;
}

double Parser::getEscenarioAncho() const {
	return escenario_ancho;
}

double Parser::getPersonajeAlto() const {
	return personaje_alto;
}

double Parser::getPersonajeAncho() const {
	return personaje_ancho;
}

int Parser::getPersonajeZindex() const {
	return personaje_zindex;
}

const Json::Reader& Parser::getReader() const {
	return reader;
}

const Json::Value& Parser::getRoot() const {
	return root;
}

int Parser::getVentanaAltopx() const {
	return ventana_altopx;
}

double Parser::getVentanaAncho() const {
	return ventana_ancho;
}

int Parser::getVentanaAnchopx() const {
	return ventana_anchopx;
}

const string& Parser::getEntrada() const {
	return entrada;
}

double Parser::getPersonajeSpritesAncho() const {
	return personaje_sprites_ancho;
}

void Parser::setPersonajeSpritesAncho(double personajeSpritesAncho) {
	personaje_sprites_ancho = personajeSpritesAncho;
}

const string& Parser::getPersonajeSpritesImagen() const {
	return personaje_sprites_imagen;
}

void Parser::setPersonajeSpritesImagen(const string& personajeSpritesImagen) {
	personaje_sprites_imagen = personajeSpritesImagen;
}

void Parser::setEntrada(const string& entrada) {
	this->entrada = entrada;
}

int Parser::getEscenarioYpiso() const {
	return escenario_ypiso;
}
