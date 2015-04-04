/*
 * Parser.cpp
 *
 *  Created on: 24/3/2015
 *      Author: ariel
 */

#include "Parser.h"

#include <jsoncpp/json/value.h>
#include <iostream>

#include "../utils/Logger.h"

Parser::Parser() {
	this->entrada = "archivo_json_defecto";
	this->ventana = new Ventana();
	this->escenario = new Escenario();
	this->capas = new list<Capa*>;
	this->personaje = new Personaje();
	this->bienParseado = false;
	this->existe_archivo = false;

	this->inicializar();
}

Parser::Parser(string archivo_json)
{
	this->entrada = archivo_json;
	this->ventana = new Ventana();
	this->escenario = new Escenario();
	this->capas = new list<Capa*>;
	this->personaje = new Personaje();
	this->bienParseado = false;
	this->existe_archivo = false;

	this->inicializar();
}

void Parser::inicializar()
{
	FILE* fd = fopen(this->entrada.c_str(),"r");
	if ( fd != NULL )
	{
		this->existe_archivo = true;
		ifstream archivo_escenario(this->entrada.c_str());
		this->bienParseado = this->reader.parse(archivo_escenario, this->root, false);
	}
	else
	{
		Logger::getInstance()->error("No existe el archivo "+this->entrada);
	}

}

void Parser::parsearDesdeJson() {

	 if( !this->bienParseado )
	 {
	   Logger::getInstance()->error("No se pudo parsear con JSON. "+reader.getFormatedErrorMessages());
	   Logger::getInstance()->info("Se va a cargar un escenario por defecto");
	   this->crearEscenerioPorDefecto();
	 }
	 else
	 {
		 if( root.size() > 0 ) {

			//atributos de la ventana
			int v_alto_px = 0;
			double v_ancho = 0;
			int v_ancho_px = 0;
			double v_margen_x = 0;

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
			int p_direccion = 0;

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
							else if ( key_nivel2.asString() == "margen_x" )
							{
								v_margen_x= (*it)["margen_x"].asDouble();
							}
							else
							{
								cout<<"parametro "<<key_nivel2.asString()<< "no encontrado!"<<endl;
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
							else if ( key_nivel2.asString() == "direccion" )
							{
								p_direccion = (*it)["direccion"].asInt();
							}
							else
							{
								cout<<"parametro no encontrado!"<<endl;
							}
						}
						else
						{
							cout<<"Loggear la lectura de una tag invalido"<<endl;
						}
					}
	 			}
	 		}

			this->ventana = new Ventana(v_ancho_px, v_alto_px, v_ancho, v_margen_x);
			this->escenario = new Escenario(e_ancho, e_alto, e_ypiso);
			this->personaje = new Personaje(p_ancho, p_alto, p_zindex, p_sprites_imagen, p_sprites_ancho, p_direccion);

	 	}
	 }

	 this->inciarValidacionSemantica();

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

void Parser::crearEscenerioPorDefecto() {

	this->ventana = new Ventana(800, 600, 200, 2);
	this->escenario = new Escenario(1000, 150, 20);
	this->personaje = new Personaje(20, 35, 1, "zubzero-caminando.png", 15, 1);

	Capa* capa_1 = new Capa("capa_1.png", 900);
	Capa* capa_2 = new Capa("capa_2.png", 800);

	capas->push_back(capa_1);
	capas->push_back(capa_2);
}

void Parser::inciarValidacionSemantica() {

	//validar el escenario
	double escenario_ancho_nuevo = this->escenario->getAncho();
	double escenario_alto_nuevo = this->escenario->getAlto();
	int escenario_ypiso_nuevo = this->escenario->getYpiso();
	if ( escenario_ancho_nuevo <= 0 )
	{
		escenario_ancho_nuevo = 1200;
	}

	if ( escenario_alto_nuevo <= 0 )
	{
		escenario_alto_nuevo = 170;
	}

	if ( escenario_ypiso_nuevo < 0 )
	{
		escenario_ypiso_nuevo = 15;
	}
	delete this->escenario;
	this->escenario = NULL;
	this->escenario = new Escenario(escenario_ancho_nuevo, escenario_alto_nuevo, escenario_ypiso_nuevo);

	//validar la ventana
	int ventana_anchopx_nuevo = this->ventana->getAnchoPx();
	int ventana_altopx_nuevo = this->ventana->getAltoPx();
	double ventana_ancho_nuevo = this->ventana->getAncho();
	double ventana_margenx_nuevo = this->ventana->getMargenX();
	//TODO continuar....

	//validar el personaje

	//validar las capas

}
