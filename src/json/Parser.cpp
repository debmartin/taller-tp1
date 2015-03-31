/*
 * Parser.cpp
 *
 *  Created on: 24/3/2015
 *      Author: ariel
 */

#include "Parser.h"
#include <fstream>

Parser::Parser() {
	this->entrada = "archivo_json_defecto";
	this->ventana = new Ventana();
	this->escenario = new Escenario();
	this->capas = new list<Capa*>;
	this->inicializar();
}

Parser::Parser(string archivo_json)
{
	this->entrada = archivo_json;
	this->ventana = new Ventana();
	this->escenario = new Escenario();
	this->capas = new list<Capa*>;
	this->inicializar();
}

void Parser::inicializar()
{
	ifstream archivo_escenario(this->entrada.c_str());
	this->bienParseado = this->reader.parse(archivo_escenario, this->root, false);
}

void Parser::parsearDesdeJson() {

	 if( !this->bienParseado )
	 {
	   // Report failures and their locations in the document.
	   cout<<"Failed to parse JSON"<<endl
	       <<reader.getFormatedErrorMessages()
	       <<endl;
	 }
	 else
	 {
		 if( root.size() > 0 ) {

			//atributos de la ventana
			int v_alto_px = 0;
			double v_ancho = 0;
			int v_ancho_px = 0;

			//atributos del escenario
			double e_alto = 0;
			double e_ancho = 0;
			int e_ypiso = 0;

			//atributos del personaje
			double p_alto = 0;
			double p_ancho = 0;
			int p_zindex = 0;
			string p_sprites_imagen = "";
			double p_sprites_ancho = 0;

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
							Capa* capa;
							string imagen_fondo = "";
							double ancho = 0;
							for( Json::ValueIterator it3 = root2[idx_capas].begin() ; it3 != root2[idx_capas].end() ; it3++ )
							{

								const Json::Value key_nivel2 = it3.key();

								if ( key_nivel2.asString() == "imagen_fondo" )
								{
									imagen_fondo = (*it)[idx_capas]["imagen_fondo"].asString();
								}
								else if ( key_nivel2.asString() == "ancho" )
								{
									ancho = (*it)[idx_capas]["ancho"].asDouble();
								}
								else
								{
									cout<<"parametro no encontrado!"<<endl;
								}
							}
							capa = new Capa(imagen_fondo, ancho);
							capas->push_back(capa);
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
								v_alto_px = (*it)["altopx"].asInt();
							}
							else if ( key_nivel2.asString() == "ancho" )
							{
								v_ancho = (*it)["ancho"].asDouble();
							}
							else if ( key_nivel2.asString() == "anchopx" )
							{
								v_ancho_px = (*it)["anchopx"].asInt();
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
								e_alto = (*it)["alto"].asDouble();
							}
							else if ( key_nivel2.asString() == "ancho" )
							{
								e_ancho = (*it)["ancho"].asDouble();
							}
							//TODO revisar porque este parametro tiene una longitud mas grande. mide 7 en vez de 5!
							else if ( key_nivel2.asString().compare("ypiso") >= 0 )
							{
								e_ypiso = (*it)[key_nivel2.asString()].asInt();
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
								p_alto = (*it)["alto"].asDouble();
							}
							else if ( key_nivel2.asString().compare("ancho") == 0 )
							{
								p_ancho = (*it)[key_nivel2.asString()].asDouble();
							}
							else if ( key_nivel2.asString().compare("zindex") >= 0 )
							{
								p_zindex = (*it)[key_nivel2.asString()].asInt();
							}
							else if ( key_nivel2.asString() == "sprites" )
							{
								p_sprites_imagen = (*it2)["imagen"].asString();
								p_sprites_ancho = (*it2)["ancho"].asDouble();
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

			this->ventana = new Ventana(v_ancho_px, v_alto_px, v_ancho);
			this->escenario = new Escenario(e_ancho, e_alto, e_ypiso);
			this->personaje = new Personaje(p_ancho, p_alto, p_zindex, p_sprites_imagen, p_sprites_ancho);

	 	}
	 }
}

Parser::~Parser() {
	// TODO Auto-generated destructor stub
}

list<Capa*>* Parser::getCapas() const {
	return capas;
}

Escenario* Parser::getEscenario() const {
	return escenario;
}

Personaje* Parser::getPersonaje() const {
	return personaje;
}

Ventana* Parser::getVentana() const {
	return ventana;
}
